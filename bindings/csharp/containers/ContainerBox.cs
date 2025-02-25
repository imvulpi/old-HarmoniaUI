using Godot;
using Godot.Collections;
using HarmoniaUI.core.systems.alert;
using System;
using static HarmoniaUI.core.Harmonia;

// You can remove the namespace or change it to Godot.
// This would include the container when creating new script through Godot.
namespace HarmoniaUI.containers
{
    public partial class ContainerBox : Control
    {
        public Visibility Visibility {
            get
            {
                return (Visibility)Call("get_visibility").AsInt32();
            }
            set
            {
                Call("set_visibility", (int)value);
            }
        }
        public const string ALERT_LAYOUT_CHANGE = "layout-change";

        public float WidthPx
        {
            get { return GetWidth(Unit.Pixel); }
            set { SetWidth(Unit.Pixel, value); }
        }

        public float HeightPx
        {
            get { return GetWidth(Unit.Pixel); }
            set { SetWidth(Unit.Pixel, value); }
        }

        public bool Debug
        {
            get { return Call("get_debug_outputs").AsBool(); }
            set { Call("set_debug_outputs", value); }
        }

        private AlertManager _alertManager;

        public AlertManager AlertManager
        {
            get
            {
                if (_alertManager == null)
                {
                    var obj = Call("get_alert_manager").AsGodotObject();
                    _alertManager = new(obj);
                    return _alertManager;
                }
                else
                {
                    return _alertManager;
                }
            }
            set { Call("set_alert_manager", value); }
        }

        public Positioning Positioning
        {
            get { return (Positioning)Call("get_position_type").AsInt32(); }
            set { Call("set_position_type", (int)value); }
        }

        public float PositionX
        {
            get { return GetPositionX(Unit.Pixel); }
            set { SetPositionX(Unit.Pixel, value); }
        }
        public float PositionY
        {
            get { return GetPositionY(Unit.Pixel); }
            set { SetPositionY(Unit.Pixel, value); }
        }

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

        public OverflowBehaviour OverflowBehaviour
        {
            get { return (OverflowBehaviour)Call("get_overflow_behaviour").AsInt32(); }
            set { Call("set_overflow_behaviour", (int)value); }
        }

        public NodePath HorizontalScroll
        {
            get { return Call("get_horizontal_scroll").AsNodePath(); }
            set { Call("set_horizontal_scroll", value); }
        }

        public string ScrollXStepStr
        {
            get { return Call("get_string_scroll_x_step").AsString(); }
            set { Call("set_string_scroll_x_step", value); }
        }

        public NodePath VerticalScroll
        {
            get { return Call("get_vertical_scroll").AsNodePath(); }
            set { Call("set_vertical_scroll", value); }
        }

        public string ScrollYStepStr
        {
            get { return Call("get_string_scroll_y_step").AsString(); }
            set { Call("set_string_scroll_y_step", value); }
        }

        public float MarginUp
        {
            get { return GetMarginUp(Unit.Pixel); }
            set { SetMarginUp(value, Unit.Pixel); }
        }
        public float MarginLeft
        {
            get { return GetMarginLeft(Unit.Pixel); }
            set { SetMarginLeft(value, Unit.Pixel); }
        }
        public float MarginDown
        {
            get { return GetMarginDown(Unit.Pixel); }
            set { SetMarginDown(value, Unit.Pixel); }
        }
        public float MarginRight
        {
            get { return GetMarginRight(Unit.Pixel); }
            set { SetMarginRight(value, Unit.Pixel); }
        }

        public float PaddingUp
        {
            get { return GetPaddingUp(Unit.Pixel); }
            set { SetPaddingUp(value, Unit.Pixel); }
        }
        public float PaddingLeft
        {
            get { return GetPaddingLeft(Unit.Pixel); }
            set { SetPaddingLeft(value, Unit.Pixel); }
        }
        public float PaddingDown
        {
            get { return GetPaddingDown(Unit.Pixel); }
            set { SetPaddingDown(value, Unit.Pixel); }
        }
        public float PaddingRight
        {
            get { return GetPaddingRight(Unit.Pixel); }
            set { SetPaddingRight(value, Unit.Pixel); }
        }

        public Color BackgroundColor
        {
            get { return Call("get_background_color").AsColor(); }
            set { Call("set_background_color", value); }
        }

        public float GetWidth(Unit unit)
        {
            return (float)Call("get_width", (int)unit).AsDouble();
        }

        public void SetWidth(Unit unit, float value)
        {
            Call("set_width", (double)value, (int)Unit.Pixel);
        }

        public string GetWidthStr()
        {
            return Call("get_width_str").AsString();
        }

        public void SetWidthStr(string value)
        {
            Call("set_width_str", value);
        }

        public string GetHeightStr()
        {
            return Call("get_height_str").AsString();
        }

        public void SetHeightStr(string value)
        {
            Call("set_height_str", value);
        }

        public float GetHeight(Unit unit)
        {
            return (float)Call("get_height", (int)unit).AsDouble();
        }

        public void SetHeight(Unit unit, float value)
        {
            Call("set_height", (double)value, (int)Unit.Pixel);
        }

        public float GetPositionX(Unit unit)
        {
            return (float)Call("get_pos_x", (int)unit).AsDouble();
        }

        public float GetPositionY(Unit unit)
        {
            return (float)Call("get_pos_y", (int)unit).AsDouble();
        }
        public float SetPositionX(Unit unit, float positionX)
        {
            return (float)Call("set_pos_x", positionX, (int)unit).AsDouble();
        }

        public float SetPositionY(Unit unit, float positionY)
        {
            return (float)Call("set_pos_y", positionY, (int)unit).AsDouble();
        }

        public string GetPositionXStr()
        {
            return Call("get_pos_x_str").AsString();
        }
        public string GetPositionYStr()
        {
            return Call("get_pos_y_str").AsString();
        }

        public void SetPositionXStr(string positionX)
        {
            Call("set_pos_x_str", positionX);
        }
        public void SetPositionYStr(string positionY)
        {
            Call("set_pos_y_str", positionY);
        }

        public void SetMarginsAll(float allSidesValue, Unit unitType, bool dispatchAlert = true)
        {
            Call("set_margin_all", (double)allSidesValue, (int)unitType, dispatchAlert);
        }

        public void SetMarginYVertical(float verticalSidesValue, Unit unitType, bool dispatchAlert = true)
        {
            Call("set_margin_y_vertical", (double)verticalSidesValue, (int)unitType, dispatchAlert);
        }
        
        public void SetMarginXHorizontal(float horizontalSidesValue, Unit unitType, bool dispatchAlert = true)
        {
            Call("set_margin_x_horizontal", (double)horizontalSidesValue, (int)unitType, dispatchAlert);
        }

        [Obsolete("Temporarily - Bug with HarmoniaUI")]
        public Array<float> GetMarginsAll(Unit unitType, bool dispatchAlert = true)
        {
            return Call("get_margins", (int)unitType, dispatchAlert).AsGodotArray<float>();
        }

        public string GetMarginStr()
        {
            return Call("get_margin_str").AsString();
        }

        public void SetMarginStr(string margins)
        {
            Call("set_margin_str", margins);
        }

        public float GetMarginUp(Unit unitType)
        {
            return (float)Call("get_margin_up", (int)unitType).AsDouble();
        }

        public void SetMarginUp(float marginValue, Unit unitType, bool dispatchAlert = true)
        { 
            Call("set_margin_up", marginValue, (int)unitType, dispatchAlert);
        }
        public float GetMarginRight(Unit unitType)
        {
            return (float) Call("get_margin_right", (int)unitType).AsDouble();
        }

        public void SetMarginRight(float marginValue, Unit unitType, bool dispatchAlert = true)
        {
            Call("set_margin_right", marginValue, (int)unitType, dispatchAlert);
        }
        public float GetMarginDown(Unit unitType)
        {
            return (float) Call("get_margin_down", (int)unitType).AsDouble();
        }

        public void SetMarginDown(float marginValue, Unit unitType, bool dispatchAlert = true)
        {
            Call("set_margin_down", marginValue, (int)unitType, dispatchAlert);
        }
        public float GetMarginLeft(Unit unitType)
        {
            return (float) Call("get_margin_left", (int)unitType).AsDouble();
        }

        public void SetMarginLeft(float marginValue, Unit unitType, bool dispatchAlert = true)
        {
            Call("set_margin_left", marginValue, (int)unitType, dispatchAlert);
        }

        public void SetPaddingsAll(float allSidesValue, Unit unitType, bool dispatchAlert = true)
        {
            Call("set_padding_all", (double)allSidesValue, (int)unitType, dispatchAlert);
        }

        public void SetPaddingYVertical(float verticalSidesValue, Unit unitType, bool dispatchAlert = true)
        {
            Call("set_padding_y_vertical", (double)verticalSidesValue, (int)unitType, dispatchAlert);
        }

        public void SetPaddingXHorizontal(float horizontalSidesValue, Unit unitType, bool dispatchAlert = true)
        {
            Call("set_padding_x_horizontal", (double)horizontalSidesValue, (int)unitType, dispatchAlert);
        }

        [Obsolete("Temporarily - Bug with HarmoniaUI")]
        public Array<float> GetPaddingsAll(Unit unitType)
        {
            return Call("get_paddings", (int)unitType).AsGodotArray<float>();
        }

        public string GetPaddingStr()
        {
            return Call("get_padding_str").AsString();
        }

        public void SetPaddingStr(string paddings)
        {
            Call("set_padding_str", paddings);
        }

        public float GetPaddingUp(Unit unitType)
        {
            return (float)Call("get_padding_up", (int)unitType).AsDouble();
        }

        public void SetPaddingUp(float paddingValue, Unit unitType, bool dispatchAlert = true)
        {
            Call("set_padding_up", paddingValue, (int)unitType, dispatchAlert);
        }
        public float GetPaddingRight(Unit unitType)
        {
            return (float)Call("get_padding_right", (int)unitType).AsDouble();
        }

        public void SetPaddingRight(float paddingValue, Unit unitType, bool dispatchAlert = true)
        {
            Call("set_padding_right", paddingValue, (int)unitType, dispatchAlert);
        }
        public float GetPaddingDown(Unit unitType)
        {
            return (float)Call("get_padding_down", (int)unitType).AsDouble();
        }

        public void SetPaddingDown(float paddingValue, Unit unitType, bool dispatchAlert = true)
        {
            Call("set_padding_down", paddingValue, (int)unitType, dispatchAlert);
        }
        public float GetPaddingLeft(Unit unitType)
        {
            return (float)Call("get_padding_left", (int)unitType).AsDouble();
        }

        public void SetPaddingLeft(float paddingValue, Unit unitType, bool dispatchAlert = true)
        {
            Call("set_padding_left", paddingValue, (int)unitType, dispatchAlert);
        }

        public void UpdatePresentation()
        {
            Call("update_presentation");
        }
    }
}
