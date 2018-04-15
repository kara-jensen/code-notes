/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//QML ENGINE / QT QUICK
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/************************************************************************************************************
===========================================================================================================
QML MEMORY ALLOCATION
===========================================================================================================
• Using QML allocates both in C++ heap and javascript garbage collected heap
• WorkerScripts share their own seperate Javascript heap, only allocated if WorkerScript is used
• Adding custom properties makes it an implicit type of the component (allocates memory for new type) 
• Not adding custom properties makes it an explicit type of the component (shares memory for type)

C++ HEAP ALLOCATIONS:
• Overhead of the QML engine (implementation data structures, context information)
• Per-component compiled data and type information, depending which modules/components used
• Per-object C++ data/property values, plus metaobject hierarchy, depending which modules/components used
• Any data which is allocated specifically by QML libraries

JAVASCRIPT HEAP ALLOCATIONS:
• Javascript engine itself including built in types
• Javascript integration: constructor functions for loaded types, function templates
• Variables allocated during expression evaluation
• Per-type layout information and other internal type-data generated by the JavaScript engine at runtime
• Per-object JavaScript data: var properties, functions/signal handlers, non-optimized binding expressions

===========================================================================================================
QML SCENE GRAPH
===========================================================================================================
• Low-level, high-performance rendering stack that renders QML visual items using OpenGL by default
• Allows the scene to be retained between frames and complete set of primitives is known before rendering
• Allows optimizations such as batch rendering to minimize state changes and discarding obscured primitives
• Managed and rendered by the QQuickWindow class 
• Three render loop types: Basic/Windows uses main thread, Threaded uses dedicated thread
• Render loop type auto chosen for hardware, usually Threaded, QSG_RENDER_LOOP forces type
  
SCENE GRAPH NODES
• Added by subclassing QQuickItem::updatePaintNode and setting the QQuickItem::ItemHasContents flag
• Only use classes with the "QSG" prefix inside the QQuickItem::updatePaintNode
• To preprocess, set QSGNode::UsePreprocess and override QSGNode::preprocess; called before rendering
• Each node uses a material (simple OpenGL shader program)

SCENE GRAPH NODE TYPES:
QSGClipNode           Implements the clipping functionality in the scene graph
QSGGeometryNode       Used for all rendered content, describes the shape/mesh of the primitive
QSGNode               The base class for all nodes in the scene graph
QSGOpacityNode        Used to change opacity of nodes
QSGTransformNode      Implements transformations in the scene graph
QSGSimpleRectNode     QSGGeometryNode which defines a rectangular geometry with a solid color material
QSGSimpleTextureNode  QSGGeometryNode which defines a rectangular geometry with a texture material

SCENE GRAPH THREADED RENDER LOOP:
1) QQuickItem::update called when QML scene changed
2) Render thread prepares to draw a new frame
3) Meanwhile GUI thread calls QQuickItem::updatePolish to do final item touch-up
4) GUI thread is blocked
5) QQuickWindow::beforeSynchronizing signal is emitted
6) Synchronization of the QML state into the scene graph by calling QQuickItem::updatePaintNode
7) GUI thread block is released
8) The scene graph is rendered:
     1) QQuickWindow::beforeRendering signal is emitted
     2) QSGNode::preprocess called for those that use it
     3) Renderer processes the nodes and calls OpenGL functions
     4) QQuickWindow::afterRendering signal is emitted
     5) Rendered frame is swapped and QQuickWindow::frameSwapped is emitted
9) Meanwhile GUI is free to advance animations, process events, etc

===========================================================================================================
QML INPUT FOCUS
===========================================================================================================

ACTIVE FOCUS:
• Item currently receives keyboard input
• Or item is a FocusScope ancestor of the item that currently receives keyboard input
**************************************************************************************************************/
    
// QQuickWindow
// Inherits QWindow, window for QML applications

// QQuickView 
// Wrapper for QQuickWindow to automatically load and display a QML scene from an url

// QQuickWidget
// Wrapper for QQuickWindow to automatically load and display a QML scene from an url
// Less stacking order restrictions, though slower compared to QQuickWindow/QQuickView
// Disables the threaded render loop on all platforms
// Avoid calling winId; triggers creation of a native window, resulting in reduced performance

// QQuickItem
// Inherits QObject, instantiated by Item QML component
// Properties have accessors item.property() and item.setProperty()
item.activeFocus // Read only, whether item has active focus
item.activeFocusOnTab // Whether included in active focus on tab, default false
item.antialiasing // Whether antialiasing enable, default false
item.baselineOffset // Position offset, default 0, used for text
item.childrenRect // Read only, QRectF collective position and size of the item's children
item.clip // Whether clipping enabled, default false, hides part of item/children, performance hit
item.enabled // Recursive, whether the item receives mouse and keyboard events
item.focus // Whether item has input focus
item.height // Actual height of item
item.width // Actual width of item
item.implicitHeight // Default height of the Item if no height is specified
item.implicitWidth // Default width of the Item if no width is specified
item.opacity // Alpha of item, values outside [0,1] clamped
item.objectName // Inherited from QObject
item.parent // QQuickItem*, visual parent of the item
item.rotation // rotation of the item in degrees clockwise around its transformOrigin, default 0
item.scale // size of item, negative mirror's item, default 1
item.smooth // Image interpolation, true is linear, false is nearest neighbour, default true
item.state // QString state name, default empty
item.transformOrigin // TransformOrigin type which scale/rotate use
item.visible // Recursive, whether item is rendered
item.x / item.y / item.z // Position and stacking depth of item, negative z draws under parent
item.childAt(x, y) // Returns first visible QQuickItem* child found at point within item coord system
item.childItems() // Returns QList<QQuickItem*>
item.componentComplete() // Called when the item has been instantiated
item.contains(point) // If item contains QPointF (in local coordinates)
item.cursor() // Returns QCursor enum for cursor type when mouse over item, default Qt::ArrowCursor
item.flag() // Returns Flags enum value
item.forceActiveFocus(reason) // Focuses item and any parent FocusScopes, reason optional
item.grabMouse() // Item will receive all mouse events until ungrabMouse is called
item.isComponentComplete() // If construction of the QML component is complete
item.isFocusScope() // If item is a FocusScope
item.keepMouseGrab() // Whether mouse input should exclusively remain with this item
item.mapFromGlobal(point) // Returns converted global QPointF to item local coord system
item.mapFromItem(item2, point) // Returns converted QPointF in item2 coord system to item local coord system
item.mapFromScene(point) // Returns converted scene QPointF to item local coord system
item.mapRectFromItem(item2, rect) // Returns converted QRectF in item2 coord system to item local coord system
item.mapRectFromScene(rect) // Returns converted scene QRectF to item local coord system
item.mapRectToItem(item2, rect)
item.mapRectToScene(rect)
item.mapToGlobal(point)
item.mapToItem(item2, point)
item.mapToScene(point)
item.nextItemInFocusChain(forward)
item.polish()
item.releaseResources()
item.scopedFocusItem()
item.setCursor(cursor)
item.setFlags(flags)
item.stackAfter(sibling)
item.ungrabMouse()
item.update()
item.updatePaintNode(oldNode, nodeData)
item.updatePolish()
item.widthValid()
item.heightValid()
item.window()
 
// QQuickPaintedItem
// Inherits QQuickItem, allows rendering content using QPainter

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QT MODELING LANGUAGE (QML)
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

import QtQuick 2.6
import QtQuick.Controls 1.4
import MyEnums 1.0
  
// Item
// Base for all QML components, instantiates QQuickItem
Item {
    id: item                               // unique id of item, can be used to access it
    property bool myProperty: true         // custom property
    property int myEnum: MyEnum.ONE        // enum property
    property int myProperty: myFunction    // if property used in function changes, re-evaluates property
    property alias myAlias: myProperty     // reference for property
    
    /* Called when the item has been instantiated */
    Component.onCompleted: {}

    /* Called when the item is destroyed */
    Component.onDestruction: {}

    /* Called when the property has changed */
    onMyPropertyChanged: {}

    /* Javascript custom function */
    function myFunction(x, y) {
        return x + y;
    }
}

item.activeFocus // Read only, whether item has active focus
item.activeFocusOnTab // Whether included in active focus on tab, default false
item.antialiasing // Whether antialiasing enable, default false
item.baselineOffset // Position offset, default 0, used for text
item.childrenRect // Read only, QRectF collective position and size of the item's children
item.clip // Whether clipping enabled, default false, hides part of item/children, performance hit
item.enabled // Recursive, whether the item receives mouse and keyboard events
item.focus // Whether item has input focus
item.height // Actual height of item
item.width // Actual width of item
item.implicitHeight // Default height of the Item if no height is specified
item.implicitWidth // Default width of the Item if no width is specified
item.opacity // Alpha of item, values outside [0,1] clamped
item.objectName // Inherited from QObject
item.parent // QQuickItem*, visual parent of the item
item.rotation // rotation of the item in degrees clockwise around its transformOrigin, default 0
item.scale // size of item, negative mirror's item, default 1
item.smooth // Image interpolation, true is linear, false is nearest neighbour, default true
item.transformOrigin // TransformOrigin type which scale/rotate use
item.visible // Recursive, whether item is rendered
item.x / item.y / item.z // Position and stacking depth of item, negative z draws under parent
item.anchors // Sub options: top, bottom, left, right, horizontalCenter, verticalCenter, baseLine
item.anchors.fill // Takes QQuickItem parent or sibling, set to undefined to detach
item.anchors.centerIn // Takes QQuickItem parent or sibling, set to undefined to detach
item.anchors.margins // Set value for all margins
item.anchors.topMargin // Set value for top margin
item.anchors.bottomMargin // Set value for bottom margin
item.anchors.leftMargin // Set value for left margin
item.anchors.rightMargin // Set value for right margin
item.anchors.horizontalCenterOffset // Value offset from horizontal center
item.anchors.verticalCenterOffset // Value offset from vertical center
item.anchors.baselineOffset // Value offset from position
item.anchors.alignWhenCentered // forces centered anchors to align to a whole pixel, default true
item.data // list<Object> of both visual children and resources
item.layer.effect // Component, typically a ShaderEffect component
item.layer.enabled // Whether the item is layered or not, disabled by default
item.layer.format // Enum, internal OpenGL format of the texture
item.layer.mipmap // Whether mipmaps are generated for the texture
item.layer.samplerName // Name of the effect's source texture property
item.layer.samples // Enum, allows requesting multisampled rendering in the layer
item.layer.smooth // Whether the layer is smoothly transformed
item.layer.sourceRect // The rectangular area of the item that should be rendered into the texture
item.layer.textureMirroring // Enum, how the generated OpenGL texture should be mirrored
item.layer.textureSize // Pixel size of the layers texture, if empty (default) uses item's size
item.layer.wrapMode // Enum, OpenGL wrap modes associated with the texture
item.resources // list<Object>, contains non-visual children
item.state // QString state name, default empty
item.states // list<State>, list of possible states for this item
item.transform // list<Transform>, list of transformations to apply
item.transitions // list<Transition>, transitions to be applied to the item whenever it changes its state
item.visibleChildren // list<Item>, contains visual children
item.childAt(x, y)
item.contains(point)
item.forceActiveFocus(reason)
item.forceActiveFocus()
item.grabToImage(callback, targetSize)
item.mapFromGlobal(x, y)
item.mapFromItem(item2, x, y, w, h)
item.mapFromItem(item2, x, y)
item.mapToGlobal(x, y)
item.mapToItem(item2, x, y, w, h)
item.mapToItem(item2, x, y)
item.nextItemInFocusChain(forward)

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QML COMPONENTS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// MouseArea
MouseArea {
    hoverEnabled: true
    acceptedButtons: Qt.RightButton | Qt.LeftButton | Qt.AllButtons
    onPressed: {}
    onRelease: {}
    onClicked: {
        var clickX = mouse.x;
        var clickY = mouse.y;
        var button = mouse.button;
    }
}

// Menu
// Call using id.popup() to show at mouse position
Menu {
    visible: false
    MenuItem {
        text: "Item"
        iconSource: "qrc:///icon.png"
        enabled: true
        onTriggered: {}
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QML LAYOUTS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Use these on any components inside the layout
Layout.alignment: Qt.AlignVCenter | Qt.AlignRight
Layout.fillHeight: true
Layout.fillWidth: true
Layout.preferredHeight: 30
Layout.preferredWidth: 30

// RowLayout
// Aligns elements after each other in a single row
RowLayout {
    spacing: 5
    anchors.fill: parent // Still use anchors on base
}

// ColumnLayout
// Aligns elements after each other in a single column
ColumnLayout {
    spacing: 5
    anchors.fill: parent // Still use anchors on base
}

// GridLayout
// Aligns elements in a grid with n columns
GridLayout {
    columns: 3
    spacing: 5
    anchors.fill: parent // Still use anchors on base
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QML WIDGETS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Rectangle
Rectangle {
    color: "#8EACFF"
    radius: 2
    border.color: "red"
    border.width: 1      
}

// Text
Text {
    text: "text"
    verticalAlignment: Text.AlignVCenter
    font.pointSize: 14
    font.bold: true
}

// Button
Button {
    iconSource: "qrc:///icon.png"
    enabled: true
    onClicked: {}
}

// ProgressBar
ProgressBar {
    maximumValue: 20
    minimumValue: 0
    style: ProgressBarStyle {
        background: Rectangle {
            radius: 2
            color: "grey"
            implicitWidth: 100
            implicitHeight: 20
        }
        progress: Rectangle {
            color: "blue"
        }
    }
}

//Dialog
Dialog {
    visible: false // Turning on/off will show dialog window
    title: "Title"
    width: 300
    height: 80
    contentItem: Rectangle {
        anchors.fill: parent
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QML VIEWS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ScrollView {
    Layout.fillWidth: true
    Layout.fillHeight: true
    ListView {
        id: listView
        Layout.fillWidth: true
        Layout.fillHeight: true
        model: context_model // Set through C++

        onCurrentIndexChanged: {
            console.log("Selected " + currentIndex);
        }          
        onCurrentItemChanged: {
            console.log("Selected " + currentItem);
        }
        
        // Each item of the model is instantiated with the delegate
        delegate: Item {
            property bool isHighlighted: mouseArea.containsMouse
            property bool isSelected: listView.currentIndex == index
            MouseArea {
                id: mouseArea
                anchors.fill: parent
                hoverEnabled: true
                acceptedButtons: Qt.RightButton | Qt.LeftButton
                onPressed: { listView.currentIndex = index; }
                onClicked: { listView.currentIndex = index; }
            }                   
            Text {
                width: listView.width
                height: 30
                text: role_name // Set through C++
            }
        }
    }
}


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// DEBUGGING QML
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/************************************************************************************************************
QT CREATOR QML DEBUGGING
1) In the Run Settings, Debugger Settings section, select the Enable QML 
2) Window > Output Panes > Debugger Console allows executing javascript during a break
3) Use the Locals and Expressions views to explore/change the QML item structure
 
PROFILING QML
1) Ensure project built with QML debugging infrastructure
2) Run: app.exe -qmljsdebugger=port:<port>
3) Should output: QML Debugger: Waiting for connection on port <port>
4) Enter console command: qmlprofiler -p <port> -attach <ip address>
**************************************************************************************************************/

QML_IMPORT_TRACE // enable debug output from QML's import loading 
QT_DECLARATIVE_DEBUG / QT_QML_DEBUG // enable the debugging infrastructure

Qt.quit() // Quits the application
console.log("Message")
console.debug("Message")
console.info("Message")
console.warn("Message")
console.error("Message")
console.assert(exp, "Message on fail")
console.time("timerName") / console.timeEnd("timerName") // log the time (in milliseconds) between the calls
console.trace() // prints stack trace
console.profile() / console.profileEnd() 
console.exception("Message") // prints message and stack trace
  
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// QML OPTIMIZATIONS
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/************************************************************************************************************
PROPERTY OPTIMIZATIONS:
• Avoid declaring with var keyword unless type is QVariantMap/variant
• Using a propery resolves it; faster to store result in local and access that
      var rectColor = rect.color; // resolve the common base.
      printValue("red", rectColor.r);
      printValue("green", rectColor.g)
• Avoid lots of writes to Q_PROPERTIES especially if has notify signal, pefer temp while initialising
      var tempProperty = [];
      tempProperty.length = 100;
      for (var i = 0; i < 100; ++i) {
          tempProperty[i] = i;
      }
      qProperty = tempProperty;
• Avoid binding as container[index] as it will re-evaluate when any container member is changed, do instead
      property int intermediateBinding: cointainer[index]
      property int firstBinding: intermediateBinding + x;
      property int secondBinding: intermediateBinding + y;

PROPERTY BINDING OPTIMZATIONS:
• Avoid declaring intermediate JavaScript variables
• Avoid accessing "var" properties
• Avoid calling JavaScript functions
• Avoid constructing closures or defining functions within the binding expression
• Avoid accessing properties outside of the immediate evaluation scope (non-component properties)
• Avoid writing to other properties
• Prefer binding to anchors over using another component's height/width properties

JAVASCRIPT OPTIMIZATIONS:
• Avoid using eval() if at all possible
• Do not delete properties of objects

COMPONENT OPTIMIZATIONS:
• If a component has a custom property, it becomes its own implicit type. 
  If more than one of these used, move to own file to save memory
• Consider using an asynchronous Loader component
• Prefer Item over invisible Rectangles
• For global data, use singleton types instead of pragma library scripts
  
RENDERING OPTIMIZATIONS:
• Set asynchronous property of images to true for loading
• Set sourceSize property for images to the exact size you want to ensure only what's needed is cached
• Avoid smoothing images using the smooth property
• May be better to disable bindings before and animation and re-enable once finished
• Avoid running JavaScript during animation
• Avoid enabling clipping
• Opaque faster than translucent, only one pixel needed to be considered translucent

MODEL/VIEW OPTIMIZATIONS
• Use WorkerScript with ListModel to move processing to another thread if needed
• Avoid setting the ListModel dynamicRoles property to true
• Avoid using ShaderEffect elements within delegates
• Never enable clipping on a delegate
• Use view cacheBuffer property to allow asynchronous creation and buffering of
  delegates outside of the visible area, at a memory usage increase cost
**************************************************************************************************************/
