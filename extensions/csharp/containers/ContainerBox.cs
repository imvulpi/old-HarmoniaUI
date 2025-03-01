using Godot;
using Godot.Collections;
using HarmoniaUI.core.systems.alert;
using System;
using static HarmoniaUI.core.Harmonia;

// You can remove the namespace or change it to Godot.
// This would include the container when creating new script through Godot.
namespace HarmoniaUI.containers
{
    /// <summary>
    /// Represents a UI container that manages layout, positioning, paddings, margins, and other related properties.
    /// Provides methods for handling visibility, event binding, layout management.
    /// </summary>
    public partial class ContainerBox : Control
    {
        public ContainerBox() {
            _instance = this;
        }
        public ContainerBox(GodotObject godotObject)
        {
            if (godotObject.IsClass("ContainerBox"))
            {
                _instance = godotObject;
            }
        }

        /// <summary>
        /// Internal object instance used for calling internal functions.
        /// </summary>
        /// <remarks>
        /// This field serves as a reference to the internal API that the C# bindings 
        /// interact with. It is used to invoke underlying functionality.
        /// </remarks>
        private GodotObject _instance;

        /// <summary>
        /// Gets or sets the visibility of the container.
        /// </summary>
        /// <remarks>
        /// This property interacts with internal methods to update or retrieve 
        /// the container's visibility state.
        /// </remarks>
        public Visibility Visibility {
            get
            {
                return (Visibility)_instance.Call("get_visibility").AsInt32();
            }
            set
            {
                _instance.Call("set_visibility", (int)value);
            }
        }

        /// <summary>
        /// Constant alert name for layout change.
        /// </summary>
        /// <remarks>
        /// This constant is used to identify layout change events within the system, 
        /// allowing components to respond accordingly.
        /// </remarks>
        public const string ALERT_LAYOUT_CHANGE = "layout-change";

        /// <summary>
        /// Gets or sets the width in pixels.
        /// </summary>
        /// <remarks>
        /// This property interacts with internal methods to retrieve or update the width of the element in pixels.
        /// </remarks>
        public float WidthPx
        {
            get { return GetWidth(Unit.Pixel); }
            set { SetWidth(Unit.Pixel, value); }
        }

        /// <summary>
        /// Gets or sets the height in pixels.
        /// </summary>
        /// <remarks>
        /// This property interacts with internal methods to retrieve or update the height of the element in pixels.
        /// </remarks>
        public float HeightPx
        {
            get { return GetWidth(Unit.Pixel); }
            set { SetWidth(Unit.Pixel, value); }
        }

        /// <summary>
        /// Gets or sets the debug output state.
        /// </summary>
        /// <remarks>
        /// Helps HarmoniaUI Developers debug the plugin.
        /// This property enables or disables debug outputs by interacting with internal methods.
        /// When enabled, additional debug information may be logged.
        /// </remarks>
        public bool Debug
        {
            get { return _instance.Call("get_debug_outputs").AsBool(); }
            set { _instance.Call("set_debug_outputs", value); }
        }

        /// <summary>
        /// Internal reference to the alert manager instance.
        /// </summary>
        /// <remarks>
        /// This field stores the alert manager used for handling alerts within the system.
        /// </remarks>
        private AlertManager _alertManager;
        
        /// <summary>
        /// Gets the alert manager instance.
        /// </summary>
        /// <remarks>
        /// This property provides access to the alert manager, which is responsible 
        /// for managing and dispatching alerts.
        /// </remarks>
        public AlertManager AlertManager
        {
            get
            {
                if (_alertManager == null)
                {
                    var obj = _instance.Call("get_alert_manager").AsGodotObject();
                    _alertManager = new(obj);
                    return _alertManager;
                }
                else
                {
                    return _alertManager;
                }
            }
            set { _instance.Call("set_alert_manager", value); }
        }

        /// <summary>
        /// Gets or sets the positioning type of the element.
        /// </summary>
        /// <remarks>
        /// This property interacts with internal methods to retrieve or update the 
        /// positioning type, determining how the element is placed within its container.
        /// </remarks>
        public Positioning Positioning
        {
            get { return (Positioning)_instance.Call("get_position_type").AsInt32(); }
            set { _instance.Call("set_position_type", (int)value); }
        }

        /// <summary>
        /// Gets or sets the X position in Pixels of the element.
        /// </summary>
        /// <remarks>
        /// This property interacts with internal methods to retrieve or update the 
        /// horizontal position of the element.
        /// </remarks>
        public float PositionX
        {
            get { return GetPositionX(Unit.Pixel); }
            set { SetPositionX(Unit.Pixel, value); }
        }

        /// <summary>
        /// Gets or sets the Y position in Pixels of the element.
        /// </summary>
        /// <remarks>
        /// This property interacts with internal methods to retrieve or update the 
        /// vertical position of the element.
        /// </remarks>
        public float PositionY
        {
            get { return GetPositionY(Unit.Pixel); }
            set { SetPositionY(Unit.Pixel, value); }
        }

        /// <summary>
        /// Gets or sets the position of the element as a Vector2.
        /// </summary>
        /// <remarks>
        /// This property provides access to both the X and Y coordinates as a single 
        /// Vector2 structure, allowing for easier manipulation.
        /// </remarks>
        public new Vector2 Position
        {
            get
            {
                float x = GetPositionX(Unit.Pixel);
                float y = GetPositionY(Unit.Pixel);
                return new Vector2(x, y);
            }
            set
            {
                SetPositionX(Unit.Pixel, value.X);
                SetPositionY(Unit.Pixel, value.Y);
            }
        }

        /// <summary>
        /// Gets or sets the overflow behavior of the element.
        /// </summary>
        /// <remarks>
        /// This property determines how the element handles content that exceeds its bounds, 
        /// such as clipping, scrolling or visible.
        /// </remarks>
        public OverflowBehaviour OverflowBehaviour
        {
            get { return (OverflowBehaviour)_instance.Call("get_overflow_behaviour").AsInt32(); }
            set { _instance.Call("set_overflow_behaviour", (int)value); }
        }

        /// <summary>
        /// Gets or sets the horizontal scroll node path.
        /// </summary>
        /// <remarks>
        /// This property interacts with internal methods to retrieve the node path of horizontal scroll element
        /// Used in editor so Node can be selected as the horizontal scroll element.
        /// </remarks>
        public NodePath HorizontalScroll
        {
            get { return _instance.Call("get_horizontal_scroll").AsNodePath(); }
            set { _instance.Call("set_horizontal_scroll", value); }
        }

        /// <summary>
        /// Gets or sets the step value for horizontal scrolling in various unit types.
        /// </summary>
        /// <remarks>
        /// This property determines the increment by which the horizontal scroll position changes.
        /// </remarks>
        public string ScrollXStepStr
        {
            get { return _instance.Call("get_string_scroll_x_step").AsString(); }
            set { _instance.Call("set_string_scroll_x_step", value); }
        }

        /// <summary>
        /// Gets or sets the vertical scroll node path.
        /// </summary>
        /// <remarks>
        /// This property interacts with internal methods to retrieve the node path of vertical scroll element
        /// Used in editor so Node can be selected as the vertical scroll element.
        /// </remarks>
        public NodePath VerticalScroll
        {
            get { return _instance.Call("get_vertical_scroll").AsNodePath(); }
            set { _instance.Call("set_vertical_scroll", value); }
        }

        /// <summary>
        /// Gets or sets the step value for vertical scrolling in various unit types.
        /// </summary>
        /// <remarks>
        /// This property determines the increment by which the vertical scroll position changes.
        /// </remarks>
        public string ScrollYStepStr
        {
            get { return _instance.Call("get_string_scroll_y_step").AsString(); }
            set { _instance.Call("set_string_scroll_y_step", value); }
        }

        /// <summary>
        /// Gets or sets the top margin in pixels.
        /// </summary>
        /// <remarks>
        /// This property provides a shorthand for accessing the pixel value of the top margin.
        /// </remarks>
        public float MarginUp
        {
            get { return GetMarginUp(Unit.Pixel); }
            set { SetMarginUp(value, Unit.Pixel); }
        }

        /// <summary>
        /// Gets or sets the left margin in pixels.
        /// </summary>
        /// <remarks>
        /// This property provides a shorthand for accessing the pixel value of the left margin.
        /// </remarks>
        public float MarginLeft
        {
            get { return GetMarginLeft(Unit.Pixel); }
            set { SetMarginLeft(value, Unit.Pixel); }
        }

        /// <summary>
        /// Gets or sets the bottom margin in pixels.
        /// </summary>
        /// <remarks>
        /// This property provides a shorthand for accessing the pixel value of the bottom margin.
        /// </remarks>
        public float MarginDown
        {
            get { return GetMarginDown(Unit.Pixel); }
            set { SetMarginDown(value, Unit.Pixel); }
        }

        /// <summary>
        /// Gets or sets the right margin in pixels.
        /// </summary>
        /// <remarks>
        /// This property provides a shorthand for accessing the pixel value of the right margin.
        /// </remarks>
        public float MarginRight
        {
            get { return GetMarginRight(Unit.Pixel); }
            set { SetMarginRight(value, Unit.Pixel); }
        }

        /// <summary>
        /// Gets or sets the top padding in pixels.
        /// </summary>
        /// <remarks>
        /// This property provides a shorthand for accessing the pixel value of the top padding.
        /// </remarks>
        public float PaddingUp
        {
            get { return GetPaddingUp(Unit.Pixel); }
            set { SetPaddingUp(value, Unit.Pixel); }
        }

        /// <summary>
        /// Gets or sets the left padding in pixels.
        /// </summary>
        /// <remarks>
        /// This property provides a shorthand for accessing the pixel value of the left padding.
        /// </remarks>
        public float PaddingLeft
        {
            get { return GetPaddingLeft(Unit.Pixel); }
            set { SetPaddingLeft(value, Unit.Pixel); }
        }

        /// <summary>
        /// Gets or sets the bottom padding in pixels.
        /// </summary>
        /// <remarks>
        /// This property provides a shorthand for accessing the pixel value of the bottom padding.
        /// </remarks>
        public float PaddingDown
        {
            get { return GetPaddingDown(Unit.Pixel); }
            set { SetPaddingDown(value, Unit.Pixel); }
        }

        /// <summary>
        /// Gets or sets the right padding in pixels.
        /// </summary>
        /// <remarks>
        /// This property provides a shorthand for accessing the pixel value of the right padding.
        /// </remarks>
        public float PaddingRight
        {
            get { return GetPaddingRight(Unit.Pixel); }
            set { SetPaddingRight(value, Unit.Pixel); }
        }

        /// <summary>
        /// Gets or sets the background color of the container.
        /// </summary>
        /// <remarks>
        /// This property interacts with internal methods to retrieve or update the 
        /// background color of the container.
        /// </remarks>
        public Color BackgroundColor
        {
            get { return _instance.Call("get_background_color").AsColor(); }
            set { _instance.Call("set_background_color", value); }
        }

        /// <summary>
        /// Retrieves the width of the element in the specified unit.
        /// </summary>
        /// <param name="unit">The unit type to retrieve the width in.</param>
        /// <returns>The width of the element in the specified unit.</returns>
        /// <remarks>
        /// This method calls internal functions to obtain the width in the requested unit type.
        /// </remarks>
        public float GetWidth(Unit unit)
        {
            return (float)_instance.Call("get_width", (int)unit).AsDouble();
        }

        /// <summary>
        /// Sets the width of the element using a specified unit and value.
        /// </summary>
        /// <param name="unit">The unit type for the width value.</param>
        /// <param name="value">The width value in the given unit.</param>
        /// <remarks>
        /// This method calls internal functions to update the element's width using the specified unit type.
        /// </remarks>
        public void SetWidth(Unit unit, float value)
        {
            _instance.Call("set_width", (double)value, (int)unit);
        }

        /// <summary>
        /// Retrieves the last set width string value.
        /// </summary>
        /// <returns>The last assigned width value as a string.</returns>
        /// <remarks>
        /// This method returns the stored string value used to set the width. 
        /// It may not reflect the actual width if width wasn't set using a string
        /// </remarks>
        public string GetWidthStr()
        {
            return _instance.Call("get_width_str").AsString();
        }

        /// <summary>
        /// Sets the width of the element using a string value.
        /// </summary>
        /// <param name="value">The width value as a string.</param>
        /// <remarks>
        /// This method allows setting the width using a string, which can include units.
        /// </remarks>
        public void SetWidthStr(string value)
        {
            _instance.Call("set_width_str", value);
        }

        /// <summary>
        /// Retrieves the height of the element in the specified unit.
        /// </summary>
        /// <param name="unit">The unit type to retrieve the height in.</param>
        /// <returns>The height of the element in the specified unit.</returns>
        /// <remarks>
        /// This method calls internal functions to obtain the height in the requested unit type.
        /// </remarks>
        public float GetHeight(Unit unit)
        {
            return (float)_instance.Call("get_height", (int)unit).AsDouble();
        }

        /// <summary>
        /// Sets the height of the element using a specified unit and value.
        /// </summary>
        /// <param name="unit">The unit type for the height value.</param>
        /// <param name="value">The height value in the given unit.</param>
        /// <remarks>
        /// This method calls internal functions to update the element's height using the specified unit type.
        /// </remarks>
        public void SetHeight(Unit unit, float value)
        {
            _instance.Call("set_height", (double)value, (int)Unit.Pixel);
        }

        /// <summary>
        /// Retrieves the last set height string value.
        /// </summary>
        /// <returns>The last assigned height value as a string.</returns>
        /// <remarks>
        /// This method returns the stored string value used to set the height. 
        /// It may not reflect the actual height if height wasn't set using a string
        /// </remarks>
        public string GetHeightStr()
        {
            return _instance.Call("get_height_str").AsString();
        }

        /// <summary>
        /// Sets the height of the element using a string value.
        /// </summary>
        /// <param name="value">The height value as a string.</param>
        /// <remarks>
        /// This method allows setting the height using a string, which can include units.
        /// </remarks>
        public void SetHeightStr(string value)
        {
            _instance.Call("set_height_str", value);
        }

        /// <summary>
        /// Retrieves the X position of the element in the specified unit.
        /// </summary>
        /// <param name="unit">The unit type to retrieve the X position in.</param>
        /// <returns>The X position of the element in the specified unit.</returns>
        /// <remarks>
        /// This method calls internal functions to obtain the X position in the requested unit type.
        /// </remarks>
        public float GetPositionX(Unit unit)
        {
            return (float)_instance.Call("get_pos_x", (int)unit).AsDouble();
        }

        /// <summary>
        /// Retrieves the Y position of the element in the specified unit.
        /// </summary>
        /// <param name="unit">The unit type to retrieve the Y position in.</param>
        /// <returns>The Y position of the element in the specified unit.</returns>
        /// <remarks>
        /// This method calls internal functions to obtain the Y position in the requested unit type.
        /// </remarks>
        public float GetPositionY(Unit unit)
        {
            return (float)_instance.Call("get_pos_y", (int)unit).AsDouble();
        }

        /// <summary>
        /// Sets the X position of the element using a specified unit and value.
        /// </summary>
        /// <param name="unit">The unit type for the X position value.</param>
        /// <param name="positionX">The X position value in the given unit.</param>
        /// <remarks>
        /// This method calls internal functions to update the element's X position using the specified unit type.
        /// </remarks>
        public float SetPositionX(Unit unit, float positionX)
        {
            return (float)_instance.Call("set_pos_x", positionX, (int)unit).AsDouble();
        }

        /// <summary>
        /// Sets the Y position of the element using a specified unit and value.
        /// </summary>
        /// <param name="unit">The unit type for the Y position value.</param>
        /// <param name="positionY">The Y position value in the given unit.</param>
        /// <remarks>
        /// This method calls internal functions to update the element's Y position using the specified unit type.
        /// </remarks>
        public float SetPositionY(Unit unit, float positionY)
        {
            return (float)_instance.Call("set_pos_y", positionY, (int)unit).AsDouble();
        }

        /// <summary>
        /// Retrieves the last set X position string value.
        /// </summary>
        /// <returns>The last assigned X position value as a string.</returns>
        /// <remarks>
        /// This method returns the stored string value used to set the X position. 
        /// It may not reflect the actual position if position wasn't set using a string
        /// </remarks>
        public string GetPositionXStr()
        {
            return _instance.Call("get_pos_x_str").AsString();
        }

        /// <summary>
        /// Retrieves the last set Y position string value.
        /// </summary>
        /// <returns>The last assigned Y position value as a string.</returns>
        /// <remarks>
        /// This method returns the stored string value used to set the Y position. 
        /// It may not reflect the actual position if position wasn't set using a string
        /// </remarks>
        public string GetPositionYStr()
        {
            return _instance.Call("get_pos_y_str").AsString();
        }

        /// <summary>
        /// Sets the X position of the element using a string value.
        /// </summary>
        /// <param name="positionX">The X position value as a string.</param>
        /// <remarks>
        /// This method allows setting the X position using a string, which can include units.
        /// </remarks>
        public void SetPositionXStr(string positionX)
        {
            _instance.Call("set_pos_x_str", positionX);
        }

        /// <summary>
        /// Sets the Y position of the element using a string value.
        /// </summary>
        /// <param name="positionY">The Y position value as a string.</param>
        /// <remarks>
        /// This method allows setting the Y position using a string, which can include units.
        /// </remarks>
        public void SetPositionYStr(string positionY)
        {
            _instance.Call("set_pos_y_str", positionY);
        }

        /// <summary>
        /// Sets the margin for all sides using the specified value and unit type.
        /// </summary>
        /// <param name="allSidesValue">The margin value to apply to all sides.</param>
        /// <param name="unitType">The unit type for the margin value.</param>
        /// <param name="dispatchAlert">Determines whether an alert should be dispatched.</param>
        public void SetMarginsAll(float allSidesValue, Unit unitType, bool dispatchAlert = true)
        {
            _instance.Call("set_margin_all", (double)allSidesValue, (int)unitType, dispatchAlert);
        }

        /// <summary>
        /// Sets the vertical margins (top and bottom) using the specified value and unit type.
        /// </summary>
        /// <param name="verticalSidesValue">The margin value to apply to the top and bottom.</param>
        /// <param name="unitType">The unit type for the margin value.</param>
        /// <param name="dispatchAlert">Determines whether an alert should be dispatched.</param>
        public void SetMarginYVertical(float verticalSidesValue, Unit unitType, bool dispatchAlert = true)
        {
            _instance.Call("set_margin_y_vertical", (double)verticalSidesValue, (int)unitType, dispatchAlert);
        }

        /// <summary>
        /// Sets the horizontal margins (left and right) using the specified value and unit type.
        /// </summary>
        /// <param name="horizontalSidesValue">The margin value to apply to the left and right.</param>
        /// <param name="unitType">The unit type for the margin value.</param>
        /// <param name="dispatchAlert">Determines whether an alert should be dispatched.</param>
        public void SetMarginXHorizontal(float horizontalSidesValue, Unit unitType, bool dispatchAlert = true)
        {
            _instance.Call("set_margin_x_horizontal", (double)horizontalSidesValue, (int)unitType, dispatchAlert);
        }

        /// <summary>
        /// Retrieves all margin values as a typed array in the specified unit type.
        /// </summary>
        /// <param name="unitType">The unit type for the margin values.</param>
        /// <param name="dispatchAlert">Determines whether an alert should be dispatched.</param>
        /// <returns>
        /// A float array containing margin values in the following order:<br></br>
        /// [0] = Top (Up) <br></br>
        /// [1] = Right <br></br>
        /// [2] = Bottom (Down) <br></br>
        /// [3] = Left <br></br>
        /// </returns>
        /// <remarks>
        /// This method is a helper function to get all margins as an ordered array.
        /// </remarks>
        [Obsolete("Temporarily - Bug with HarmoniaUI")]
        public Array<float> GetMarginsAll(Unit unitType, bool dispatchAlert = true)
        {
            return _instance.Call("get_margins", (int)unitType, dispatchAlert).AsGodotArray<float>();
        }

        /// <summary>
        /// Retrieves the last set string margin value.
        /// </summary>
        /// <returns>The last assigned margin string value.</returns>
        /// <remarks>
        /// This method returns the stored string value used to set the margins. 
        /// It may not reflect the actual margin if margin wasn't set using a string
        /// </remarks>
        public string GetMarginStr()
        {
            return _instance.Call("get_margin_str").AsString();
        }

        /// <summary>
        /// Sets the margins using a string value.
        /// </summary>
        /// <param name="margins">The margin value as a string.</param>
        /// <remarks>
        /// This method allows setting the margins using a string, which can include units.
        /// </remarks>
        public void SetMarginStr(string margins)
        {
            _instance.Call("set_margin_str", margins);
        }

        /// <summary>
        /// Retrieves the top margin in the specified unit type.
        /// </summary>
        /// <param name="unitType">The unit type for the margin value.</param>
        /// <returns>The top margin value.</returns>
        public float GetMarginUp(Unit unitType)
        {
            return (float)_instance.Call("get_margin_up", (int)unitType).AsDouble();
        }

        /// <summary>
        /// Sets the top margin using the specified value and unit type.
        /// </summary>
        /// <param name="marginValue">The margin value to set.</param>
        /// <param name="unitType">The unit type for the margin value.</param>
        /// <param name="dispatchAlert">Determines whether an alert should be dispatched.</param>
        public void SetMarginUp(float marginValue, Unit unitType, bool dispatchAlert = true)
        { 
            _instance.Call("set_margin_up", marginValue, (int)unitType, dispatchAlert);
        }

        /// <summary>
        /// Retrieves the right margin in the specified unit type.
        /// </summary>
        /// <param name="unitType">The unit type for the margin value.</param>
        /// <returns>The right margin value.</returns>
        public float GetMarginRight(Unit unitType)
        {
            return (float) _instance.Call("get_margin_right", (int)unitType).AsDouble();
        }

        /// <summary>
        /// Sets the right margin using the specified value and unit type.
        /// </summary>
        /// <param name="marginValue">The margin value to set.</param>
        /// <param name="unitType">The unit type for the margin value.</param>
        /// <param name="dispatchAlert">Determines whether an alert should be dispatched.</param>
        public void SetMarginRight(float marginValue, Unit unitType, bool dispatchAlert = true)
        {
            _instance.Call("set_margin_right", marginValue, (int)unitType, dispatchAlert);
        }

        /// <summary>
        /// Retrieves the bottom margin in the specified unit type.
        /// </summary>
        /// <param name="unitType">The unit type for the margin value.</param>
        /// <returns>The bottom margin value.</returns>
        public float GetMarginDown(Unit unitType)
        {
            return (float) _instance.Call("get_margin_down", (int)unitType).AsDouble();
        }

        /// <summary>
        /// Sets the bottom margin using the specified value and unit type.
        /// </summary>
        /// <param name="marginValue">The margin value to set.</param>
        /// <param name="unitType">The unit type for the margin value.</param>
        /// <param name="dispatchAlert">Determines whether an alert should be dispatched.</param>
        public void SetMarginDown(float marginValue, Unit unitType, bool dispatchAlert = true)
        {
            _instance.Call("set_margin_down", marginValue, (int)unitType, dispatchAlert);
        }

        /// <summary>
        /// Retrieves the left margin in the specified unit type.
        /// </summary>
        /// <param name="unitType">The unit type for the margin value.</param>
        /// <returns>The left margin value.</returns>
        public float GetMarginLeft(Unit unitType)
        {
            return (float) _instance.Call("get_margin_left", (int)unitType).AsDouble();
        }

        /// <summary>
        /// Sets the left margin using the specified value and unit type.
        /// </summary>
        /// <param name="marginValue">The margin value to set.</param>
        /// <param name="unitType">The unit type for the margin value.</param>
        /// <param name="dispatchAlert">Determines whether an alert should be dispatched.</param>
        public void SetMarginLeft(float marginValue, Unit unitType, bool dispatchAlert = true)
        {
            _instance.Call("set_margin_left", marginValue, (int)unitType, dispatchAlert);
        }

        /// <summary>
        /// Sets the padding for all sides using the specified value and unit type.
        /// </summary>
        /// <param name="allSidesValue">The padding value to apply to all sides.</param>
        /// <param name="unitType">The unit type for the padding value.</param>
        /// <param name="dispatchAlert">Determines whether an alert should be dispatched.</param>
        public void SetPaddingsAll(float allSidesValue, Unit unitType, bool dispatchAlert = true)
        {
            _instance.Call("set_padding_all", (double)allSidesValue, (int)unitType, dispatchAlert);
        }

        /// <summary>
        /// Sets the vertical paddings (top and bottom) using the specified value and unit type.
        /// </summary>
        /// <param name="verticalSidesValue">The padding value to apply to the top and bottom.</param>
        /// <param name="unitType">The unit type for the padding value.</param>
        /// <param name="dispatchAlert">Determines whether an alert should be dispatched.</param>
        public void SetPaddingYVertical(float verticalSidesValue, Unit unitType, bool dispatchAlert = true)
        {
            _instance.Call("set_padding_y_vertical", (double)verticalSidesValue, (int)unitType, dispatchAlert);
        }

        /// <summary>
        /// Sets the horizontal paddings (left and right) using the specified value and unit type.
        /// </summary>
        /// <param name="horizontalSidesValue">The padding value to apply to the left and right.</param>
        /// <param name="unitType">The unit type for the padding value.</param>
        /// <param name="dispatchAlert">Determines whether an alert should be dispatched.</param>
        public void SetPaddingXHorizontal(float horizontalSidesValue, Unit unitType, bool dispatchAlert = true)
        {
            _instance.Call("set_padding_x_horizontal", (double)horizontalSidesValue, (int)unitType, dispatchAlert);
        }

        /// <summary>
        /// Retrieves all padding values as a typed array in the specified unit type.
        /// </summary>
        /// <param name="unitType">The unit type for the padding values.</param>
        /// <param name="dispatchAlert">Determines whether an alert should be dispatched.</param>
        /// <returns>
        /// A float array containing padding values in the following order:  
        /// [0] = Top (Up)  
        /// [1] = Right  
        /// [2] = Bottom (Down)  
        /// [3] = Left  
        /// </returns>
        /// <remarks>
        /// This method is a helper function to get all paddings as an ordered array.
        /// </remarks>
        [Obsolete("Temporarily - Bug with HarmoniaUI")]
        public Array<float> GetPaddingsAll(Unit unitType)
        {
            return _instance.Call("get_paddings", (int)unitType).AsGodotArray<float>();
        }

        /// <summary>
        /// Retrieves the last set string padding value.
        /// </summary>
        /// <returns>The last assigned string padding value.</returns>
        /// <remarks>
        /// This method returns the stored string value used to set the paddings. 
        /// It may not reflect the actual padding if padding wasn't set using a string
        /// </remarks>
        public string GetPaddingStr()
        {
            return _instance.Call("get_padding_str").AsString();
        }

        /// <summary>
        /// Sets the paddings using a string value.
        /// </summary>
        /// <param name="paddings">The padding value as a string.</param>
        /// <remarks>
        /// This method allows setting the paddings using a string, which can include units.
        /// </remarks>
        public void SetPaddingStr(string paddings)
        {
            _instance.Call("set_padding_str", paddings);
        }

        /// <summary>
        /// Retrieves the top padding in the specified unit type.
        /// </summary>
        /// <param name="unitType">The unit type for the padding value.</param>
        /// <returns>The top padding value.</returns>
        public float GetPaddingUp(Unit unitType)
        {
            return (float)_instance.Call("get_padding_up", (int)unitType).AsDouble();
        }

        /// <summary>
        /// Sets the top padding using the specified value and unit type.
        /// </summary>
        /// <param name="paddingValue">The padding value to set.</param>
        /// <param name="unitType">The unit type for the padding value.</param>
        /// <param name="dispatchAlert">Determines whether an alert should be dispatched.</param>
        public void SetPaddingUp(float paddingValue, Unit unitType, bool dispatchAlert = true)
        {
            _instance.Call("set_padding_up", paddingValue, (int)unitType, dispatchAlert);
        }

        /// <summary>
        /// Retrieves the right padding in the specified unit type.
        /// </summary>
        /// <param name="unitType">The unit type for the padding value.</param>
        /// <returns>The right padding value.</returns>
        public float GetPaddingRight(Unit unitType)
        {
            return (float)_instance.Call("get_padding_right", (int)unitType).AsDouble();
        }

        /// <summary>
        /// Sets the right padding using the specified value and unit type.
        /// </summary>
        /// <param name="paddingValue">The padding value to set.</param>
        /// <param name="unitType">The unit type for the padding value.</param>
        /// <param name="dispatchAlert">Determines whether an alert should be dispatched.</param>
        public void SetPaddingRight(float paddingValue, Unit unitType, bool dispatchAlert = true)
        {
            _instance.Call("set_padding_right", paddingValue, (int)unitType, dispatchAlert);
        }

        /// <summary>
        /// Retrieves the bottom padding in the specified unit type.
        /// </summary>
        /// <param name="unitType">The unit type for the padding value.</param>
        /// <returns>The bottom padding value.</returns>
        public float GetPaddingDown(Unit unitType)
        {
            return (float)_instance.Call("get_padding_down", (int)unitType).AsDouble();
        }

        /// <summary>
        /// Sets the bottom padding using the specified value and unit type.
        /// </summary>
        /// <param name="paddingValue">The padding value to set.</param>
        /// <param name="unitType">The unit type for the padding value.</param>
        /// <param name="dispatchAlert">Determines whether an alert should be dispatched.</param>
        public void SetPaddingDown(float paddingValue, Unit unitType, bool dispatchAlert = true)
        {
            _instance.Call("set_padding_down", paddingValue, (int)unitType, dispatchAlert);
        }

        /// <summary>
        /// Retrieves the left padding in the specified unit type.
        /// </summary>
        /// <param name="unitType">The unit type for the padding value.</param>
        /// <returns>The left padding value.</returns>
        public float GetPaddingLeft(Unit unitType)
        {
            return (float)_instance.Call("get_padding_left", (int)unitType).AsDouble();
        }

        /// <summary>
        /// Sets the left padding using the specified value and unit type.
        /// </summary>
        /// <param name="paddingValue">The padding value to set.</param>
        /// <param name="unitType">The unit type for the padding value.</param>
        /// <param name="dispatchAlert">Determines whether an alert should be dispatched.</param>
        public void SetPaddingLeft(float paddingValue, Unit unitType, bool dispatchAlert = true)
        {
            _instance.Call("set_padding_left", paddingValue, (int)unitType, dispatchAlert);
        }

        /// <summary>
        /// Force updates the presentation, includes updating positioning, width, height, overflow and other.
        /// </summary>
        public void UpdatePresentation()
        {
            _instance.Call("update_presentation");
        }
    }
}
