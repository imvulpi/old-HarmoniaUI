namespace HarmoniaUI.core
{
    /// <summary>
    /// Constants, enums and other related to HarmoniaUI project, This class shouldn't be an instance.
    /// </summary>
    public class Harmonia
    {
        /// <summary>
        /// Enum used for defining overflowing behaviour
        /// </summary>
        public enum OverflowBehaviour
        {
            /// <summary>
            /// Will add scrolls and hide overflowing content
            /// </summary>
            Scroll,
            /// <summary>
            /// Will hide overflowing content
            /// </summary>
            Hidden,
            /// <summary>
            /// Overflowing content will be visible.
            /// </summary>
            Visible,
        };

        /// <summary>
        /// Enum used for positioning of containers
        /// </summary>
        public enum Positioning
        {
            /// <summary>
            /// Normal
            /// </summary>
            Static,  
            /// <summary>
            /// Positioned to parent
            /// </summary>
            Absolute,
            /// <summary>
            /// Positioned from the original location
            /// </summary>
            Relative, 
        };

        /// <summary>
        /// Enum used for visibility of containers
        /// </summary>
        public enum Visibility
        {
            /// <summary>
            /// Visible container
            /// </summary>
            Visible,
            /// <summary>
            /// Hidden container no space allocated
            /// </summary>
            Hidden,
            /// <summary>
            /// Transparent container, space allocated but not visible
            /// </summary>
            Transparent
        };

        /// <summary>
        /// Enum of units that are supported by specific length and other values. 
        /// </summary>
        public enum Unit
        {
            /// <summary>
            /// Represents an unset unit.
            /// </summary>
            NotSet = -1,
            /// <summary>
            /// This is a pixel unit, written short 'px' in values, ex: '100px'
            /// </summary>
            Pixel,
            /// <summary>
            /// This is a percentage unit, written short '%' in values, ex: '10%'
            /// </summary>
            Percentage,
            /// <summary>
            /// This is a viewport width unit, written short 'vw' in values, ex: '10vw'
            /// </summary>
            ViewportWidth,
            /// <summary>
            /// This is a viewport height unit, written short 'vh' in values, ex: '10vh'
            /// </summary>
            ViewportHeight,
        };
    }
}
