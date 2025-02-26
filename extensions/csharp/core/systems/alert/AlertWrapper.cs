using Godot;

namespace HarmoniaUI.core.systems.alert
{
    /// <summary>
    /// Represents a wrapper for an internal alert instance, providing functionality to manage alert.
    /// Automatically creates an internal alert instance upon instantiation.
    /// </summary>
    public class AlertWrapper
    {
        public AlertWrapper(GodotObject godotObject)
        {
            _instance = godotObject;
        }

        public AlertWrapper()
        {
            _instance = ClassDB.Instantiate("Alert").AsGodotObject();
        }

        /// <summary>
        /// Internal instance of the alert.  
        /// This instance is created when the wrapper is instantiated.
        /// </summary>
        public GodotObject _instance;

        /// <summary>
        /// Sets the name of the alert.
        /// </summary>
        /// <param name="alertName">The name to assign to the alert.</param>
        public void SetAlertName(string alertName)
        {
            _instance.Call("set_alert_name", alertName);
        }

        /// <summary>
        /// Gets the name of the alert.
        /// </summary>
        /// <returns>The current alert name.</returns>
        public string GetAlertName()
        {
            return _instance.Call("get_alert_name").AsString();
        }
    }
}
