#if TOOLS
using Godot;
using Godot.Collections;
using harmoniaui_editor;
using System.Collections.Generic;
using System.IO;
using static harmoniaui_editor.HarmoniaEditorConstants;

[Tool]
public partial class HarmoniaUIEditor : EditorPlugin
{
    public HarmoniaEditorSettings HarmoniaEditorSettings = new();
    private Node SceneHolder { get; set; }
    private Node CurrentScene { get; set; }
    private HashSet<Node> RegisteredNodes { get; set; } = new();

    /// <summary>
    /// Handles plugin intialization, loads necessary data.
    /// Starts other processes like AutoCreation
    /// </summary>
    public override void _EnterTree()
	{
        HarmoniaEditorSettings.LoadSettings();
        AddToolMenuItem("HarmoniaUI Editor - Reload", new Callable(this, nameof(Reload)));
        HandleAutoCreation();
    }

    /// <summary>
    /// Reloads the plugin, refreshing its state
    /// </summary>
    /// <remarks>
    /// This method is used to reload configurations,
    /// or restart processes without requiring a godot restart.
    /// </remarks>
    public void Reload()
    {
        _ExitTree();
        _EnterTree();
    }

    /// <summary>
    /// Handles the automatic creation of empty scripts for newly added or loaded harmoniaui nodes 
    /// that do not have an associated script.
    /// </summary>
    /// <remarks>
    /// This method ensures that every harmoniaui node has a script by generating an empty script 
    /// when necessary.
    /// </remarks>
    public void HandleAutoCreation()
    {
        if (HarmoniaEditorSettings.AutoCreationEnabled)
        {
            var parent = GetTree()?.EditedSceneRoot?.GetParent();
            if (parent != null)
            {
                SceneHolder = parent;
                CurrentScene = GetTree()?.EditedSceneRoot;
                ConnectFirstScene();
                SetupSceneHolder();
            }
            else
            {
                SearchSceneHolder();
            }
        }
    }

    /// <summary>
    /// Sets the scene holder or searches for it at regular intervals if not found.
    /// </summary>
    /// <remarks>
    /// This method ensures that the scene holder is properly assigned. If it is not 
    /// immediately available, the function will continue searching at specified intervals 
    /// until it is found.
    /// </remarks>
    public void SetupSceneHolder()
    {
        if (IsInstanceValid(SceneHolder))
        {
            SceneHolder.ChildEnteredTree += OnSceneAdded;
        }
        else
        {
            SearchSceneHolder();
        }
    }

    /// <summary>
    /// Searches for the scene holder within the current environment.
    /// </summary>
    /// <remarks>
    /// This method attempts to locate the scene holder, ensuring that it is correctly 
    /// identified and accessible for further operations.
    /// </remarks>
    public void SearchSceneHolder()
    {
        Timer timer = new()
        {
            Autostart = true,
            WaitTime = 1
        };

        timer.Timeout += () =>
        {
            var parent = GetTree()?.EditedSceneRoot?.GetParent();
            if (parent != null)
            {
                SceneHolder = parent;
                CurrentScene = GetTree()?.EditedSceneRoot;
                SetupSceneHolder();
                ConnectFirstScene();
                timer.Stop();
                RemoveChild(timer);
            }
        };
        AddChild(timer);
    }

    /// <summary>
    /// Handles a scene being added and removed from the scene holder.
    /// </summary>
    /// <param name="node">Scene node, which is also the scene root that is being added</param>
    /// <remarks>
    /// This method is triggered when a new scene is added to the scene holder, ensuring 
    /// that any necessary setup or registration occurs and that the previous scene 
    /// is properly disconnected
    /// </remarks>
    private void OnSceneAdded(Node node)
    {
        DisconectScene();
        CurrentScene = node;
        string bindingsPath = HarmoniaEditorSettings.GetCSharpBindingsPath();
        AutoCreateScript(node, CONTAINER_INTERNAL_CLASS_NAME, Path.Join(bindingsPath, CONTAINERS_DIR, CONTAINER_BOX_SCRIPT_NAME));
        ConnectScene();
    }

    /// <summary>
    /// Handles a node being added to the scene.
    /// </summary>
    /// <param name="node">Node being added</param>
    /// <remarks>
    /// This method is triggered when a new node is added in any of the scene nodes.
    /// Automatically creates empty scripts for nodes which don't have any scripts.<br></br>
    /// You can implement your auto creates here
    /// </remarks>
    private void OnNodeAdded(Node node)
    {
        if (!RegisteredNodes.Contains(node))
        {
            RegisteredNodes.Add(node);
            node.ChildEnteredTree += OnNodeAdded;
            node.ChildExitingTree += OnNodeRemoved;
            string bindingsPath = HarmoniaEditorSettings.GetCSharpBindingsPath();
            AutoCreateScript(node, CONTAINER_INTERNAL_CLASS_NAME, Path.Join(bindingsPath, CONTAINERS_DIR, CONTAINER_BOX_SCRIPT_NAME));
        }
    }

    /// <summary>
    /// Automatically attaches a script to the specified node if it matches the given internal class name and has no script attached.
    /// </summary>
    /// <param name="nodeToCheck">The node to evaluate.</param>
    /// <param name="internalClassName">The expected internal class name of the node.</param>
    /// <param name="scriptPath">The file path of the script to be attached</param>
    /// <remarks>
    /// This method checks if the given node's internal class name matches the provided class name.
    /// If the node does not have a script attached, provided script of the specified type will be 
    /// assigned to the node. Will cause issues if script isn't deriving from/or the class of the node 
    /// provided. This method doesn't verify script classes.
    /// </remarks>

    public void AutoCreateScript(Node nodeToCheck, string internalClassName, string scriptPath)
    {
        if (nodeToCheck.IsClass(internalClassName))
        {
            Variant scriptVariant = nodeToCheck.GetScript();
            if (scriptVariant.VariantType == Variant.Type.Nil)
            {
                string bindingsPath = HarmoniaEditorSettings.GetCSharpBindingsPath();
                if (bindingsPath != null)
                {   
                    nodeToCheck.SetScript(GD.Load<Script>(scriptPath));
                }
            }

            //// Some nodes could have added children before events for it were registered
            Array<Node> containerNodes = nodeToCheck.GetChildren();
            foreach (Node containerNode in containerNodes)
            {
                if (!RegisteredNodes.Contains(containerNode))
                {
                    containerNode.ChildEnteredTree += OnNodeAdded;
                    containerNode.ChildExitingTree += OnNodeRemoved;
                    RegisteredNodes.Add(containerNode);
                }
            }
        }
    }

    /// <summary>
    /// Handles a node being removed from the scene.
    /// </summary>
    /// <param name="node">Node being removed</param>
    /// <remarks>
    /// This method is triggered when a node is removed from the scene, ensuring proper 
    /// cleanup, deregistration.
    /// </remarks>
    private void OnNodeRemoved(Node node)
    {
        if (RegisteredNodes.Contains(node))
        {
            RegisteredNodes.Remove(node);
            node.ChildEnteredTree -= OnNodeAdded;
            node.ChildExitingTree -= OnNodeRemoved;
        }
    }

    /// <summary>
    /// Disconnects the current scene when a new scene is added or an existing scene is removed.
    /// </summary>
    /// <remarks>
    /// This method ensures that the previous scene is properly disconnected.
    /// </remarks>
    public void DisconectScene()
    {
        if(IsInstanceValid(CurrentScene))
        {
            RegisteredNodes.Remove(CurrentScene);
            CurrentScene.ChildEnteredTree -= OnNodeAdded;
            CurrentScene.ChildExitingTree -= OnNodeRemoved;
        }
    }

    /// <summary>
    /// Connects the current scene and attaches necessary event listeners.
    /// </summary>
    /// <remarks>
    /// This method is responsible for setting up the scene by connecting required events 
    /// and ensuring proper initialization when a new scene is loaded.
    /// </remarks>
    public void ConnectScene()
    {
        if(IsInstanceValid(CurrentScene))
        {
            RegisteredNodes.Add(CurrentScene);
            CurrentScene.ChildEnteredTree += OnNodeAdded;
            CurrentScene.ChildExitingTree += OnNodeRemoved;
        }
    }

    /// <summary>
    /// Handles connecting the first scene when there are no other scenes present.
    /// When Godot loads the first scene might load faster than the plugin meaning
    /// that there are nodes already in the scene, this method accounts for that.
    /// </summary>
    /// <remarks>
    /// This method ensures that the initial scene is properly set up, initializing necessary 
    /// events for the application's first active scene, it also registeres all nodes within the scene.
    /// </remarks>
    public void ConnectFirstScene()
    {
        if (IsInstanceValid(CurrentScene))
        {
            CurrentScene.ChildEnteredTree += OnNodeAdded;
            CurrentScene.ChildExitingTree += OnNodeRemoved;
            List<Node> nodes = GetAllNodes(CurrentScene);
            foreach(Node node in nodes)
            {
                RegisteredNodes.Add(node);
                node.ChildEnteredTree += OnNodeAdded;
                node.ChildExitingTree += OnNodeRemoved;
            }
        }
    }

    /// <summary>
    /// Disconnects the current scene and all nodes within it.
    /// </summary>
    /// <remarks>
    /// This method ensures that the entire scene, along with its nodes, is properly 
    /// disconnected.
    /// </remarks>
    public void DisconnectAll()
    {
        if (IsInstanceValid(CurrentScene))
        {
            CurrentScene.ChildEnteredTree -= OnNodeAdded;
            CurrentScene.ChildExitingTree -= OnNodeRemoved;
            List<Node> nodes = GetAllNodes(CurrentScene);
            foreach (Node node in nodes)
            {
                RegisteredNodes.Remove(node);
                node.ChildEnteredTree -= OnNodeAdded;
                node.ChildExitingTree -= OnNodeRemoved;
            }
        }
    }

    /// <summary>
    /// Recursively retrieves all descendant nodes within the given node, excluding the root node itself.
    /// </summary>
    /// <param name="node">The root node to start the search from.</param>
    /// <param name="currentLevel">The current depth level in the recursion (default is 0).</param>
    /// <param name="allNodes">A list to store the collected nodes (default is null, initialized internally).</param>
    /// <returns>A list containing all descendant nodes of the given node.</returns>
    /// <remarks>
    /// This method traverses all children and their children recursively until the last level is reached, 
    /// effectively retrieving all nodes in the hierarchy except the initially provided node.
    /// </remarks>
    public List<Node> GetAllNodes(Node node, int currentLevel = 0, List<Node> allNodes = null)
    {
        if(currentLevel == 0)
        {
            allNodes = new();
        }

        var nodeChildren = node.GetChildren();
        foreach(Node child in nodeChildren)
        {
            allNodes.Add(child);
            allNodes = GetAllNodes(child, currentLevel + 1, allNodes);
        }
        return allNodes;
    }

    /// <summary>
    /// Handles exiting the plugin
    /// </summary>
    /// <remarks>
    /// This method performs cleanup and operations before plugin exits.
    /// </remarks>
    public override void _ExitTree()
	{
        DisconnectAll();
        RemoveToolMenuItem("HarmoniaUI Editor - Reload");
        RegisteredNodes.Clear();
        SceneHolder.ChildEnteredTree -= OnSceneAdded;
    }
}
#endif
