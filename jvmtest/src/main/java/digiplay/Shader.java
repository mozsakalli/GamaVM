package digiplay;

/**
 *
 * @author mustafa
 */
public class Shader {
    
    long deviceHandle;
    
    public Shader(String vertex, String fragment) {
        
    }
    private native static long init(String vertex, String fragment);
    
}
