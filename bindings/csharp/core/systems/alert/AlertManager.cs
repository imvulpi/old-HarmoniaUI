using Godot;

namespace HarmoniaUI.core.systems.alert
{
    public partial class AlertManager : GodotObject
    {
        public AlertManager(GodotObject instance)
        {
            _instance = instance;
        }
        public AlertManager()
        {
            _instance = ClassDB.Instantiate("AlertManager").AsGodotObject();
        }
        private GodotObject _instance;
        public void DispatchAlert(AlertWrapper alert)
        {
            _instance.Call("dispatch_alert", alert._instance);
        }

        public void AddBind(string alertType, Callable callable)
        {
            _instance.Call("add_bind", alertType, callable);
        }

        public void RemoveBind(string alertType, Callable callable)
        {
            _instance.Call("remove_bind", alertType, callable);
        }
    }
}
