using System;
using System.Text;

namespace csharp
{
    public class Writer
    {
        public StringBuilder buffer = new StringBuilder();
        int tabs;
        bool needsTabs;

        void checkTabs()
        {
            if (needsTabs)
            {
                for (int i = 0; i < tabs; i++) buffer.Append("\t");
                needsTabs = false;
            }
        }
        public Writer Write(object o) { checkTabs(); buffer.Append(o); return this; }
        public Writer WriteLn(object o) { Write(o); return Ln(); }
        public Writer Format(string format, params object[] args) => Write(string.Format(format, args));
        public Writer FormatLn(string format, params object[] args) => WriteLn(string.Format(format, args));
        public Writer Ln() { buffer.Append("\n"); needsTabs = true; return this; }
        public Writer Indent()
        {
            tabs++;
            return this;
        }
        public Writer Undent()
        {
            tabs--;
            if (tabs < 0) tabs = 0;
            return this;
        }

        public Writer Semi()
        {
            var ptr = buffer.Length - 1;
            while (ptr > 0)
            {
                var c = buffer[ptr--];
                if (c <= 32) continue;
                if (c == ';' || c == '}') return this;
                break;
            }
            return Write(";");
        }
        public Writer SemiLn()
        {
            var ptr = buffer.Length - 1;
            while (ptr > 0)
            {
                var c = buffer[ptr--];
                if (c <= 32) continue;
                if (c == ';' || c == '}') return this;
                break;
            }
            return WriteLn(";");
        }
    }
}
