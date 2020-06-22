import java.io.ByteArrayOutputStream;
import java.io.DataOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.LinkedHashMap;
import java.util.List;
import java.util.Map;

/**
 *
 * @author mustafa
 */
public class Hotreload {
    
    public static void main(String...args) {
        File root = null;
        int port = 7777;
        
        if(args.length > 0) {
            root = new File(args[0]);
        }
        if(args.length > 1)
            port = Integer.parseInt(args[1]);
        
        if(root == null || !root.exists()) {
            File temp = new File(Hotreload.class.getProtectionDomain().getCodeSource().getLocation().toExternalForm().substring(5).replace("%20", " "));
            while(root == null && temp != null) {
                File f = new File(temp, "Assets");
                if(f.exists()) {
                    root = f;
                    break;
                }
                temp = temp.getParentFile();
            }    
           //if(root == null) {
           //    System.out.println("Cant find Assets folder");
           //    return;
           //}
        }
        System.out.println("Serving "+root+" at port "+port);
        Hotreload h = new Hotreload(root, port);
    }
    
    interface AssetWalker {
        public void onAsset(File file) throws Exception;
    }
    
    File rootFolder;
    int port;
    Map<String, Long> assetFiles = new HashMap<String, Long>();
    
    public Hotreload(File rootFolder, int port) {
        this.rootFolder = rootFolder;
        this.port = port;
        try { checkAssets(true); }catch(Exception e){}
        new Thread(new Listener()).start();
    }
    
    void internalCheck(File file, List result, boolean firstTime) throws Exception {
        if(file.isDirectory()) {
            for(File f : file.listFiles()) internalCheck(f, result, firstTime);
        } else {
            if(file.isHidden() || !file.getName().contains(".")) return;
            String renamed = file.getAbsolutePath().substring(rootFolder.getAbsolutePath().length());
            if(!firstTime) {
                if(!assetFiles.containsKey(renamed) || assetFiles.get(renamed) != file.lastModified()) {
                    result.add(renamed);
                }
            }
            assetFiles.put(renamed, file.lastModified());
        }
    }
    
    List checkAssets(boolean firstTime) throws Exception {
        List result = new ArrayList();
        internalCheck(rootFolder, result, firstTime);
        return result;
    }
    
    void walkAssets(File file, AssetWalker walker) throws Exception {
        if(file.isDirectory()) {
            for(File f : file.listFiles()) walkAssets(f, walker);
        } else {
            walker.onAsset(file);
        }
    }
    
    String buildHotreload(String hash) throws Exception {
        final Map jsonMap = new LinkedHashMap();
        final Map fileMap = new LinkedHashMap();
        walkAssets(rootFolder, (file) -> {
            if(file.getName().endsWith(".xml")) {
                int len = (int)file.length();
                byte[] bytes = new byte[len];
                FileInputStream in = new FileInputStream(file);
                in.read(bytes);
                in.close();
                String rename = file.getAbsolutePath().substring(rootFolder.getAbsolutePath().length()+1).replace('\\', '/');
                jsonMap.put(rename, new String(bytes));
                fileMap.put(rename, file.getAbsolutePath());
            }
        });
        Map response = new HashMap();
        String str = Json.encode(jsonMap);
        String currentHash = String.valueOf(str.hashCode());
        if(currentHash.equals(hash)) {
            
        } else {
            response.put("hash", str.hashCode());
            response.put("json", jsonMap);
            response.put("files", fileMap);
        }
        return Json.encode(response);        
    }
    
    
    class Listener implements Runnable {

        @Override
        public void run() {
            try {
                ServerSocket socket = new ServerSocket(port);
                while(true) {
                    Socket client = socket.accept();
                    new Thread(new Worker(client)).start();
                }
            }catch(Exception e){
                System.out.println("Server stopped. Another instance running?");
                System.exit(-1);
            }
        }
        
    }
    
    class Worker implements Runnable {

        private static final String OUTPUT_HEADERS = 
                "HTTP/1.1 200 OK\r\n" +
                "Content-Type: application/json; charset=utf-8\r\n" +
                "Access-Control-Allow-Origin: *\r\n" +
                "Content-Length: ";
        private static final String OUTPUT_END_OF_HEADERS = "\r\n\r\n";

        Socket socket;
        
        public Worker(Socket socket) {
            this.socket = socket;
        }
        
        @Override
        public void run() {
            try {
                InputStream in = socket.getInputStream();
                OutputStream out = socket.getOutputStream();
                byte[] inBytes = new byte[1024*8];
                int readed = in.read(inBytes);
                String reqheader = null;
                String reqbody = null;
                for(int i=0; i<readed; i++)
                    if(inBytes[i]==10 && inBytes[i+2]==10) {
                        reqheader = new String(inBytes, 0, i);
                        if(reqheader.startsWith("POST")) {
                            ByteArrayOutputStream bytestream = new ByteArrayOutputStream();
                            String lines[] = reqheader.split("\n");
                            int contentLength = 0;
                            for(String str : lines)
                                if(str.startsWith("Content-Length:")) {
                                    contentLength = Integer.parseInt(str.substring(15).trim());
                                    break;
                                }
                            ByteArrayOutputStream bytes = new ByteArrayOutputStream();
                            int rest = readed-i-3;
                            if(rest > 0) {
                                bytes.write(inBytes, i+3, rest);
                                contentLength -= rest;
                            }
                            while(contentLength > 0) {
                                readed = in.read(inBytes);
                                if(readed > 0) {
                                    bytes.write(inBytes, 0, readed);
                                    contentLength -= readed;
                                } else break;
                            }
                            reqbody = new String(bytes.toByteArray());
                        }
                        break;
                    }
                String url = null;
                String lines[] = reqheader.split("\n");
                String fullUrl[] = lines[0].split(" ")[1].split("\\?");
                url = fullUrl[0];
                if(url != null) {
                    if(url.equals("/save-project")) {
                        /*Map reqmap = (Map)Json.decode(reqbody);
                        Map<String,String> xmls = (Map)reqmap.get("xml");
                        Map<String,String> files = (Map)reqmap.get("files");
                        for(String layName : xmls.keySet()) {
                            if(files.containsKey(layName)) {
                                File file = new File(files.get(layName));
                                file.getParentFile().mkdirs();
                                FileOutputStream outf = new FileOutputStream(file);
                                outf.write(xmls.get(layName).toString().getBytes());
                                outf.close();
                            }
                        }*/
                    } else
                    if(url.equals("/stop")) {
                        System.out.println("Hotreload server stopped by url");
                        System.exit(-1);
                        return;
                    }
                    if(url.equals("/ping")) {
                        String header =                 
                            "HTTP/1.1 200 OK\r\n" +
                            "Access-Control-Allow-Origin: *\r\n" +
                            "Content-Length: 0" + OUTPUT_END_OF_HEADERS;
                        out.write(header.getBytes());
                    } else
                    if(url.startsWith("/hotreload")) {
                        String hash = url.length() > 10 ? url.substring(10) : "";
                        String pkg = buildHotreload(hash);
                        byte[] bytes = pkg.getBytes();
                        String str = OUTPUT_HEADERS + bytes.length +  OUTPUT_END_OF_HEADERS;
                        out.write(str.getBytes());
                        out.write(bytes);
                    } else
                    if(url.startsWith("/jar")) {
                        String hash = url.length() > 4 ? url.substring(4) : "";
                        File f = new File("/Users/mustafa/Work/GamaVM/okeyextra/target/okeyextra.jar");
                        ByteArrayOutputStream ba = new ByteArrayOutputStream();
                        DataOutputStream d = new DataOutputStream(ba);
                        d.writeLong(f.lastModified());
                        if(!String.valueOf(f.lastModified()).equals(hash)) {
                            byte[] tmp = new byte[(int)f.length()];
                            new FileInputStream(f).read(tmp);
                            d.write(tmp);
                        }
                        d.flush();
                        byte[] bytes = ba.toByteArray();
                        String str = OUTPUT_HEADERS + bytes.length +  OUTPUT_END_OF_HEADERS;
                        out.write(str.getBytes());
                        out.write(bytes);
                    } 
                    else {
                        String[] search = {"", "../Web", "../Web/bin", "../Web/bin/Debug"};
                        File file = null;
                        for(String path : search) {
                            File f = new File(new File(rootFolder, path), url);
                            if(f.exists() && f.isFile()) {
                                file = f;
                                break;
                            }
                        }
                        if(file != null && file.exists() && file.isFile()) {
                            String header =                 
                                "HTTP/1.1 200 OK\r\n" +
                                //"Content-Type: application/json; charset=utf-8\r\n" +
                                "Access-Control-Allow-Origin: *\r\n" +
                                "Content-Length: "+file.length() + OUTPUT_END_OF_HEADERS;
                            out.write(header.getBytes());
                            byte[] buffer = new byte[1024*16];
                            InputStream fin = new FileInputStream(file);
                            while((readed = fin.read(buffer)) > 0) out.write(buffer, 0, readed);
                            fin.close();
                        }
                    }
                }
                out.flush();
                out.close();
            }catch(Exception e){
                e.printStackTrace();
            }
        }

    }
    
}
