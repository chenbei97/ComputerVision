# -*- coding UTF-8 -*-
'''
@Project : python学习工程文件夹
@File : Qt类规则索引.py
@Author : chenbei
@Date : 2020/10/4 9:51
'''
# 常用模块
from PyQt5.QtWidgets import  QApplication ,QDialog,QWidget ,QAbstractSpinBox,QListWidgetItem,QMenu,QToolButton
from PyQt5.QtCore import  Qt , pyqtSlot
from PyQt5.QtGui import  QPalette ,QCursor ,QIcon ,QFont
# <1>
# 常用模块说明
# 1、QtCore : 提供核心的非GUI功能的类,如QFile、QDir、QTimer、Qt(布局,对齐)、pyqtSlot、QObject(自定义信号)等
# 2、QtGui : 提供用于GUI设计的功能类,包括QIcon(添加图标)、QFont(字体格式类)、QPalette(颜色类) , QCursor(右键菜单类)
# 3、QtWidget : 提供GUI设计的窗体类型 QWiget、QDialog、QMainWindow、QAbstractSpinBox()等

# <2>
# 常用组件说明
# 1、数据输入输出组件
# 1.1、QLineEdit输入输出字符串,也可以输入输出数值型数据,只需函数内部作数字-字符串转换即可
# 1.2、QSpinBox 输入输出整数,可以二、十六进制显示    <- QAbstractSpinBox
# 1.3、QDoubleSpinBox 输入输出浮点数  <- QAbstractSpinBox
# 1.2和1.3的常用属性列表
## ----------------------------------------------------------------------------
# prefix     | 数字显示的前缀,如"$"
# suffix     | 数字显示的后缀,如"kg"
# minimum    | 数值范围的最小值,如"0"
# maximum    | 数值范围的最大值,如"100"
# singlestep | 单击右侧上下调整按钮时的单步变化值,如"1"or"2"
# value      | 当前显示的值
# displayIntegerBase | QSpinBox特有属性,显示整数使用的进制,如"2"表示二进制
# decimals   | QDoubleSpinBox特有属性,显示数值的小数位数,如"2"表示2位小数
## -------------------------------------------------------------------------------

# <3>
# 2、QPushButton组件(点击按钮)
# 2.1、checkable=True && autoExclusive=True && flat=True 可以使QPushButton具有QRadioButton的效果
#      即状态只能选择1种，如左对齐、居中、右对齐三个只能选择1个
# 2.2、checked=True && autoExclusive=False 具有QCheckBox的效果
#      即复选框，类似于粗体、下划线、斜体可以复选
# 2.3、本身的功能就是普通按钮，通过clicked信号和槽函数的关系可以实现相应功能

# <4>
# 3、QSlider、QScrollBar和QProgressBar(进度条)组件
# 3.1、QSlider和QScrollBar属性(常用信号valueChanged(int)),父类是QAbstractSlider
## ----------------------------------------------------------------------------------
# minimum/maximum  | 输入范围的最小最大值
# singleStep       | 单步长
# pageStep         | 输入焦点在组件时，按PgUp或PgDn变化的数值
# value            | 组件当前值
# sliderPosition   | 滑块位置 , 若tracking设置为True , 则等于value
# orientation      | 水平或垂直 , 枚举类型Qt.Horizontal or Qt.Vertical
# invertedAppearance | 显示方式是否反向, 默认False,数值由左至右增大
# invertedControls | 设置为True,按下PgUp或PgDn时调整数值的方向反向
# QSlider专有属性:
# tickPosition     | 刻度线的显示位置,QSlider.NoTicks(无刻度),QSlider.TicksBothSides(两边显示刻度)
# QSlider.TicksAbove、QSlider.TicksBelow、QSlider.TicksLeft、QSlider.TicksRight(上下左右显示刻度)
# tickInterval     | 标尺刻度间隔值,设置为0在singleStep和pageStep中选择
## ----------------------------------------------------------------------------

# 3.2、QProgressBar常用属性,父类是QWidget
## -------------------------------------------------------------------------
# minimum/maximum  | 输出范围的最小最大值
# value            | 组件当前值
# textVisible      | 是否显示文字,显示百分比进度
# orientation      | 水平或垂直 , 枚举类型Qt.Horizontal or Qt.Vertical
# format           | 文字格式,"%p%"显示百分比(默认),"%v"显示当前值,"%m"显示总步数
# ----------------------------------------------------------------------------

# <5>
# 4、QDate、QDateTime、QTime 时间日期类
# 4.1、QTimer 定时器(程序内部定义) , QLCDNumber 数码管显示类
# 4.2、QComboBox 下拉列表框 常用API
# ----------------------------------------------------------------------------
# currentIndex        | 当前全部项的序号 ,第一项序号为0
# currentText         | 当前全部项的文字
# currentData(role)   | 当前全部项的用户数据,role默认为Qt.UserRole, 可以为一个项定义多个角色的用户数据
# itemText(index)     | 返回索引号index的项
# itemData(index,role)| 返回索引号index且角色为role的关联数据
# count()             | 返回项目的个数
# ----------------------------------------------------------------------------

# <6>
# 6、QMainWindow(主窗体类)、QAction(创建菜单项、工具栏等)
# ----------------------------------------------------------------------------
# 6.1、项处理的类 主要包括两大类 Item Views 和 Item Widgets 类
# 6.1.1、Item Views 基于模型/视图结构 , 即视图(View)与模型数据(Model Data)实现数据的显示和编辑
# 6.1.2、Item Widgets 直接将数据存储在每一个项里
# 6.1.2.1、QListWidgets 每一行存储一个项
## ----------------------------------------------------------------------------
# 每个项属性主要有text、font、icon、textAligenment、background、foreground、flags、checkstate
# 其中flags属性较为重要,列举如下
# Selectable : 项可被选择 , 对应枚举值 Qt.ItemIsSelectable
# Editable : 项可被编辑 , 对应枚举值 Qt.ItemIsEditable
# DragEnabled : 项可被拖动 , 对应枚举值 Qt.ItemIsDragEnabled
# DropEnabled : 项可以接收拖放的项 , 对应枚举值 Qt.ItemIsDropEnabled
# UserCheckable : 项可以被复选 ,若为True 项目前出现CheckBox , 对应枚举值 Qt.ItemIsUserCheckable
# Enabled : 项可被使能 , 对应枚举值 Qt.ItemIsEnabled
# Tristate : 允许 check 的第三种状态 , 若为 False ,则只有checked 和 unchecked 两种状态 ,对应枚举值 Qt.ItemIsAutoTristate
# 一般而言Selectable、Editable、UserCheckable、Enabled 需要特别设置 ,其余默认即可
# Editable 可以用于控制项目是否可以编辑
## ----------------------------------------------------------------------------
# QListWidget常用API函数
# listWidget.clear() 清空项
# listWidget.insertItem() 插入项
# listWidget.takeItem() 删除当前项
# listWidget.item(i)  遍历项
# listWidget.currentRow() 当前项
# listWidget.count() 项总个数
# listWidget.addItem() 添加项
## --------------------------------------------------------------------------
# QListWidget常用C++槽函数
# currentRowChanged(int) 传递界面当前项的行号
# currentItemChanged(current,previous) 传递当前项和前一项
# currentTextChanged(str) 传递当前项文本内容变化的信号
## ----------------------------------------------------------------------------
# QListWidget常用的类为QListWidgetItem ,用于生成项
# 实例化的item常用的API函数为
# setText()
# setIcon()
# setCheckState() 常用枚举值Qt.Checked 用于表示项是否勾选
# setFlags()
## -----------------------------------------------------------------------------
## 6.1.2.2、QTreeWidgets 每个节点是一个项
## -----------------------------------------------------------------------------
# 常用API函数
# treeWidget.clear 清空
# treeWidget.currentItem 当前项
# treeWidget.header() 设置表头列之间的距离 setDefaultSectionSize(650) and setMinimumSectionSize(650) 设置默认和最小宽度
# treeWidget.addTopLevelItem(item) 添加顶层节点
# treeWidget.topLevelItemCount() 顶层节点个数
## -----------------------------------------------------------------------------
# 常用的类为 QTreeWidgetItem(type) 用于创建项 , 参数需要指定该节点项的类型,属于枚举参数
## -----------------------------------------------------------------------------
# QTreeWidgetItem的常用API函数: 节点类型有多列如节点列和节点类型列,必须传递type类型
# setText(type,string)
# setIcon(type,icon)
# setFont(type,font)
# setFlags(type,flags)
# setCheckState(type,Qt.checked) 设置复选框
# setTextAlignment(type,Qt.AlignVCenter | Qt.AlignHCenter)
# setData(type,Qt.UserRole,data) 给指定节点的用户角色传递相应的数据 , 例如可以在图片节点传递该图片的地址目录,并调用该数据在状态栏显示
# item.parent() 找到父节点
# item.type() 返回节点类型
# item.text() 返回命名
# item.data(type,Qt.UserRole) 返回用户数据,一般存放的是全路径
# 对于父节点还有3个API函数
# addChild(item) 添加子节点
# removeChild(item) 移除节点
# setExpanded(True) 展开节点
# childCount() 返回顶层节点的子节点个数
## -----------------------------------------------------------------------------
# 6.1.2.3、QTableWidgets 每个单元格是一个项
# ----------------------------------------------------------------------------
# 6.2、QTabWidget设计多页界面 , 可以放置动作按钮QToolButton
# ----------------------------------------------------------------------------
# 6.3、QToolBox 分组工具箱 , 在QTabWidget中使用 , 存放的是 QToolButton
# ----------------------------------------------------------------------------
# 6.4、QToolBar 工具栏 , 也可以存放QToolButton , 或者说主工具栏的按钮就是根据Action自动创建的QToolButton
# QToolBar.addSeparator 添加分割条
# QToolBar.addAction 添加动作 ,这里可以看出 QToolBar与QToolButton的共性 , 区别是QToolBar是在ui窗体设计时静态添加的
# QToolBar.addWidget(QToolButton()) 添加动态工具按钮
# ----------------------------------------------------------------------------
# 6.5、QSplitter 设计左右分割的界面 , 可以用于分割 QTabWidget 和 QToolBox
# 常常配合该代码  :  self.setCentralWidget(self.ui.splitter)
# ----------------------------------------------------------------------------
# 6.6、QDockWidget 停靠区组件 , 类似于QToolBox , 是一个区域用于存放其他组件的
# 该组件可以停靠在QMainWindow窗口 , 可以存放 QTreeWidget 树状结构图
# <7>
# 7、QToolButton
# 常用 API  如下
## ----------------------------------------------------------------------------
# setDefaultAction 设置动作和按钮关联的函数
# setMenu 设置下拉菜单
# setPopupMode 设置菜单模式 菜单有2种模式
# 分别是QToolButton.MenuButtonPopup和QToolButton.InstantPopup , 前者只能点击小三角才能出现菜单,后者点击按钮就会出现
# setToolButtonStyle 设置图标位置 ,一般使用枚举值Qt.ToolButtonTextUnderIcon
## ----------------------------------------------------------------------------

# <8>
# 8、QMenu 菜单类
# addAciton() 联系动作和菜单 ,然后只需要把菜单设置到QToolButton中即可使用
# exec(QCursor.pos()) 显示菜单
# 常与QWidget继承的内部C++槽函数customContextMenuRequested()使用,此槽函数在鼠标右键单击时即会发射信号

# <9>
# 9、QAction 设置某个动作,可以设置图标、文本、快捷键、提示文字,可以用于单独的按钮QToolButton也可以与QToolBar建立联系作为菜单使用
# 对应动作一般都是动态代码实现相应功能,也可以使用槽函数 , 如"选择项目"的triggered()就会触发槽的trigger()  , 这样可以反选时更新状态
# 或者退出动作"exit" 可以联系窗体QMyListWidget的close()函数
# 其他常用的C++槽函数全选、清空、删除等都使用triggered()信号,然后连接QListWidget常用API函数即可

# <10>
# 10、QPixmap 图片   存储当前显示的原始图片
# self.curPixmap = QPixmap()  实例化类
# 加载图片函数 : self.curPixmap.load(filename) 加载路径为filename的图片
# 常用属性 : self.curPixmap.width() 、 self.curPixmap.height()
# 常用方法 : self.curPixmap.scaled(width,height) 将图片缩放到指定的宽度和高度
# self.curPixmap.scaledToHeight 和 self.curPixmap.scaledToWidth  # scaled的拆分函数,分别指定高度和宽度
# 常配合的组件为QLabel ,通过QLabel的pixmap属性可以显示图片 , setPixmap(pix) , pix为scaled、scaledToHeight、scaledToWidth的返回值

# <11>
# 11、QScrollArea 滚动区域类 位于区域内的组件如果超出区域高度会自动产生垂直或水平方向的滚动条
# 常配合语句 : self.setCentralWidget(self.ui.ScrollArea) 将滚动区域设置为中心组件,那么该区域与其他组件会自动出现分割条
## ----------------------------------------------------------------------------
# 常用API方法
# ①setWidgetResizable(True)    自动调整scrollarea内部组件的大小
# ②setAlignment(Qt.AlignVCenter) 设置居中
# ③setMinimumSize(850,1000)  手动调节scrollarea的最小宽度与高度
# ④self.ui.ScrollArea.height() self.ui.ScrollArea.width()  获取滚动区域的高度和宽度
## ----------------------------------------------------------------------------

# <12>
# 12、QFileDialog() 文件节点类
## ----------------------------------------------------------------------------
# 常用API函数
# fileaddress = QFileDialog.getExistingDirectory() 选取文件夹,返回路径地址
# QFileDialog.getOpenFileName() 选择文件
# filelist , flitter = QFileDialog.getOpenFileNames() 选择多个文件 返回选取得文件和文件筛选类型
# QFileDialog.getSaveFileName() 选择保存文件
# fileinfo = QFileInfo(filelist)  #  <PyQt5.QtCore.QFileInfo object at 0x000001BDBD014518>
# fileinfo.fileName() # 最后一级文件名
## ----------------------------------------------------------------------------
# 常配合使用的类 QDir()
#  filedir = QDir(fileaddress)  # <PyQt5.QtCore.QDir object at 0x00000200D5C2C588>
#  filedir.dirName() 返回最后一级目录的名称 # 可以用于设置新建的目录名字

# <13>
# 13、QDockWidget 停靠区域
# 常用方法
# ①setFloating(True) 设置浮动性
# ②setVisible(False) 设置可见性
# ③setFeatures(QDockWidget.AllDockWidgetFeatures)停靠区的属性
# 枚举值为QDockWidget.DockWidgetClosable(停靠区可关闭)、QDockWidget.DockWidgetMovable(停靠区可移动)
# QDockWidget.DockWidgetFloatable(停靠区可浮动)、QDockWidget.DockWidgetVerticalTitleBar(停靠区左侧显示垂直标题栏)
# QDockWidget.AllDockWidgetFeatures(使用以上所有特征)、QDockWidget.NoDockWidgetFeatures(不能停靠、移动和关闭)
# ④setAllowedAreas(Qt.LeftDockWidgetArea|Qt.RightDockWidgetArea) 允许停靠区域
# 其他枚举值在顶部和底部 Qt.TopDockWidgetArea 、Qt.BottomDockWidgetArea 、AllDockWidgetAreas、NoDockWidgetArea、DockWidgetArea_Mask
# 常用C++槽函数
# visibilityChanged(self,visible) 组件标题栏按钮关闭时会隐藏停靠区并发射信号,利用此信号可以菜单栏将其可见
# topLevelChanged(self,toplevel) 组件浮动或者停靠时会发射信号 , 从而可以菜单栏恢复停靠