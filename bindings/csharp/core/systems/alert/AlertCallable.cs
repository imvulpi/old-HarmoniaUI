using Godot;
using System;

namespace HarmoniaUI.core.systems.alert
{
    public partial class AlertCallable : GodotObject
    {
        public AlertCallable()
        {

        }
        public event EventHandler<AlertWrapper> AlertCalled;
        public Callable GetCallable()
        {
            Callable callable = new(this, nameof(Callback));
            return callable;
        }

        private void Callback(GodotObject godotObject)
        {
            AlertWrapper alertWrapper = new(godotObject);
            AlertCalled.Invoke(this, alertWrapper);
        }
    }
}
