using System;
using System.Collections.Generic;
using dnlib.DotNet;

namespace csharp
{
    public class Cls
    {
        public TypeDef Type;
        public Dictionary<string, Cls> GenericVariants = new Dictionary<string, Cls>();
        
    }

    public class Types
    {
        public Types()
        {
        }
    }
}
