using Godot;

namespace HarmoniaUI.core.systems.alert
{
    public class AlertWrapper
    {
        public GodotObject _instance;
        public AlertWrapper(GodotObject godotObject)
        {
            _instance = godotObject;
        }

        public AlertWrapper()
        {
            _instance = ClassDB.Instantiate("Alert").AsGodotObject();
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
