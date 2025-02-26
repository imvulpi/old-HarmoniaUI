using Godot;

namespace HarmoniaUI.containers
{

    /// <summary>
    /// Empty Container Box - They have a specific icon to distinguish them from other scripts.
    /// 
    /// <para><b>DO NOT DELETE</b> unless you plan on extending the node. Otherwise, the node will not interact with Godot properly.</para>
    ///
    /// <para><b>If you plan on extending ContainerBox</b> Remove this script from the node and add a new one.
    /// The new script should implement <c>ContainerBox</c>.</para>
    ///
    /// <para><b>Example of extending:</b></para>
    /// <code>
    /// class MyContainer : ContainerBox { } // This will work correctly and interact with Godot as expected.
    /// </code>
    ///
    /// <para><b>Explanation:</b></para>
    /// <para>As of Godot 4.3, there are known issues with registering C++ GDExtension classes inside C#.
    /// Because of this, bindings or wrappers need to be developed.</para>
    /// 
    /// <para>Even with bindings, if <c>ContainerBox</c> does not have an implementation in C# (such as this one),  
    /// it may cause issues with Godot's systems, including exporting, <c>GetNode&lt;ContainerBox&gt;()</c>, and others.</para>
    /// </summary>
    [GlobalClass, Icon("res://addons/harmoniaui/EmptyContainerBox.svg")]
    public partial class EmptyContainerBox : ContainerBox
    {
    }
}
