using System;
using System.Collections.Generic;
using System.Text;
using System.ComponentModel;

namespace TerraControl
{
    class SerializableBindingList<T> : BindingList<T>
    {
        public List<T> AsList
        {
            get { return (List<T>)this.Items; }
        }
    }
}
