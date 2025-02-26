using Godot;
using System;

namespace HarmoniaUI.core.systems.alert
{
    /// <summary>
    /// Wrapper for Callable, providing a more C#-friendly event handler for alerts.
    /// Automatically converts a callback object to an <see cref="AlertWrapper"/>
    /// <br></br>
    /// <example>
    /// For example:
    /// <code>
    /// AlertCallable alertCallable = new AlertCallable();
    /// alertCallable.AlertCalled += AlertCallable_AlertCalled;
    /// AlertManager.AddBind(ALERT_LAYOUT_CHANGE, alertCallable.GetCallable()); // AlertManager of some container
    /// </code>
    /// </example>
    /// </summary>
    public partial class AlertCallable : GodotObject
    {
        public AlertCallable() { }

        /// <summary>
        /// Event triggered when an alert is dispatched.
        /// The associated <see cref="AlertWrapper"/> instance is passed as event data.
        /// </summary>
        public event EventHandler<AlertWrapper> AlertCalled;

        /// <summary>
        /// Retrieves the underlying Callable reference.
        /// </summary>
        /// <returns>The internal Callable reference.</returns>
        public Callable GetCallable()
        {
            Callable callable = new(this, nameof(Callback));
            return callable;
        }

        /// <summary>
        /// Internal callback method that executes when an alert occurs.
        /// </summary>
        /// <param name="alertObject">The internal alert object associated with the alert event</param>
        private void Callback(GodotObject alertObject)
        {
            AlertWrapper alertWrapper = new(alertObject);
            AlertCalled.Invoke(this, alertWrapper);
        }
    }
}
