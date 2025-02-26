using Godot;
using System.IO;
using static harmoniaui_editor.HarmoniaEditorConstants;

namespace harmoniaui_editor
{
    public class HarmoniaEditorSettings
    {
        public bool AutoCreationEnabled { get; set; }
        public string CSharpBindingsPath { get; set; }

        /// <summary>
        /// Loads all settings into an instance of the settings configuration.
        /// </summary>
        /// <remarks>
        /// This method retrieves and initializes all stored settings, making them accessible 
        /// for use within the plugin.
        /// </remarks>
        public void LoadSettings()
        {
            AutoCreationEnabled = GetAutoCreationSetting();
            CSharpBindingsPath = GetCSharpBindingsPath();
        }

        /// <summary>
        /// Retrieves the auto-creation setting, which enables or disables the auto-creation module.
        /// </summary>
        /// <returns><c>true</c> if auto-creation is enabled, <c>false</c> otherwise.</returns>
        /// <remarks>
        /// This method checks the stored settings and returns whether the auto-creation module 
        /// should be active.
        /// </remarks>
        public bool GetAutoCreationSetting()
        {
            ProjectSettingsInstance projectSettings = ProjectSettings.Singleton;
            if (projectSettings.HasSetting(AUTO_CREATION_SETTING))
            {
                Variant autoCreationVariant = projectSettings.GetSetting(AUTO_CREATION_SETTING);
                AutoCreationEnabled = autoCreationVariant.AsBool();
            }
            else
            {
                AutoCreationEnabled = true;
                projectSettings.SetSetting(AUTO_CREATION_SETTING, AutoCreationEnabled);
            }
            return AutoCreationEnabled;
        }

        /// <summary>
        /// Retrieves the C# bindings path from the settings.
        /// </summary>
        /// <returns>The file path to the C# bindings directory.</returns>
        /// <remarks>
        /// This method accesses the configuration to determine where C# bindings are stored 
        /// within the project structure.
        /// </remarks>
        public string GetCSharpBindingsPath()
        {
            ProjectSettingsInstance projectSettings = ProjectSettings.Singleton;
            Variant csharpBindingsPath = projectSettings.GetSetting(CSHARP_BINDINGS_PATH_SETTING);
            if (projectSettings.HasSetting(CSHARP_BINDINGS_PATH_SETTING) && Directory.Exists(ProjectSettings.GlobalizePath(csharpBindingsPath.AsString())))
            {
                CSharpBindingsPath = csharpBindingsPath.AsString();
            }
            else
            {
                GD.PrintErr("Unset HarmoniaUI C# Bindings path, Set setting harmoniaui/csharp_bindings_path to the C# bindings directory - now using default");
                projectSettings.SetSetting(CSHARP_BINDINGS_PATH_SETTING, "res://addons/harmoniaui/csharp/");
                CSharpBindingsPath = null;
            }
            return CSharpBindingsPath;
        }
    }
}
