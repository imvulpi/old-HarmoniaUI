using Godot;

namespace HarmoniaUI.core.systems.alert
{
    /// <summary>
    /// C# wrapper for the internal alert manager.  
    /// Manages alert dispatching and alert bindings.
    /// Automatically creates an internal instance upon instantiation.
    /// </summary>
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

        /// <summary>
        /// Internal instance of the alert manager.  
        /// This instance is created automatically when the wrapper is instantiated.
        /// </summary>
        private GodotObject _instance;

        /// <summary>
        /// Dispatches an alert using the provided <see cref="AlertWrapper"/> instance.
        /// </summary>
        /// <param name="alert">The alert to dispatch.</param>
        public void DispatchAlert(AlertWrapper alert)
        {
            _instance.Call("dispatch_alert", alert._instance);
        }

        /// <summary>
        /// Adds a binding to an alert type, associating it with a callable to be executed when triggered.
        /// </summary>
        /// <param name="alertType">The type of alert to bind.</param>
        /// <param name="callable">The callable to execute when the alert is triggered.</param>
        public void AddBind(string alertType, Callable callable)
        {
            _instance.Call("add_bind", alertType, callable);
        }

        /// <summary>
        /// Removes a binding from an alert type, preventing the associated callable from executing.
        /// </summary>
        /// <param name="alertType">The type of alert to unbind.</param>
        /// <param name="callable">The callable to remove from the alert binding.</param>
        public void RemoveBind(string alertType, Callable callable)
        {
            _instance.Call("remove_bind", alertType, callable);
        }
    }
}
