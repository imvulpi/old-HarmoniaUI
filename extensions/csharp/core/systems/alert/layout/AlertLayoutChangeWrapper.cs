using Godot;

namespace HarmoniaUI.core.systems.alert.layout
{
    class AlertLayoutChangeWrapper
    {
        public GodotObject _instance;
        public AlertLayoutChangeWrapper(GodotObject godotObject)
        {
            _instance = godotObject;
        }

        public AlertLayoutChangeWrapper()
        {
            _instance = ClassDB.Instantiate("AlertLayoutChange").AsGodotObject();
        }

        public void SetAlertName(string alertName)
        {
            _instance.Call("set_alert_name", alertName);
        }

        public string GetAlertName()
        {
            return _instance.Call("get_alert_name").AsString();
        }
    }
}
