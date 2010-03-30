using System;
using System.Collections.Generic;
using System.Text;
using System.ComponentModel;

namespace TerraControl
{
    [Serializable]
    public class Settings
    {
        public List<Output> outputs;
        public List<Timerswitch> timers;

        public string[] daytime;
        public string[] tempsetpoint;
        public string[] humsetpoint;
        public string name;
    }
}
