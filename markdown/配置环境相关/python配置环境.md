<1>python的安装
		1.1、安装网址：https://www.python.org/downloads/
		1.2、安装注意事项：勾选【Add Python 3.7 to PATH】，然后点击【Customize installation】，然后next
		1.2、安装注意事项网址：https://blog.csdn.net/cheng__lu/article/details/89007480
<2>pycharm的安装
		2.1、安装网址：https://www.jetbrains.com/pycharm/   (需要破解)
		2.2、破解方案：安装结束后将破解文件直接拖到主页重启即可  查看about信息2089年
		2.3、汉化方案：打开图标所在文件位置 默认在bin文件夹 退后进入lib文件夹  把汉化文件放入即可
		2.4、pycharm激活方案参考：https://www.jianshu.com/p/e995e1dd81e4
		2.5、配置用户环境变量：
			C:\Users\chenbei\AppData\Local\Programs\Python\Python37\Scripts\
			C:\Users\chenbei\AppData\Local\Programs\Python\Python37\
		2.6、安装包的方式：
				2.6.1、终端安装
						①常用命令：(win+r或者ctrl+option+/)
								pip list   查看所有库
								pip list --outdated  查看过期库
								python.exe -m pip install --upgrade pip   升级pip
								pip install --upgrade matplotlib   升级某个库
								pip uninstall xlrd
								'''    
								一键升级所有库 参考网址：https://blog.csdn.net/weixin_38997425/article/details/88782998?utm_medium=distribute.pc_aggpage_search_result.none-task-blog-2~all~first_rank_v2~rank_v25-3-88782998.nonecase&utm_term=python%E6%9B%B4%E6%96%B0%E6%89%80%E6%9C%89%E5%BA%93%E5%91%BD%E4%BB%A4
								import pip
								from subprocess import call
								from pip._internal.utils.misc import get_installed_distributions
								for dist in get_installed_distributions():
								call("pip install -i  https://pypi.tuna.tsinghua.edu.cn/simple --upgrade " + dist.project_name, shell=True)
								'''
						②解决问题：You are using pip version 19.0.3, however version 20.0.2 is available
									解决方案：https://blog.csdn.net/qq_41575507/article/details/104555139?utm_medium=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-1.nonecase&depth_1-utm_source=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-1.nonecase
									终端命令：pip3 install --index-url https://pypi.douban.com/simple numpy
				2.6.2、pycharm安装包
				2.6.3、手动安装python包
							参考方案网址：https://blog.csdn.net/dyy_csdn/article/details/81460922
							①进入网站下载安装包：https://www.lfd.uci.edu/~gohlke/pythonlibs/#numpy
							②下载后将numpy放在Python安装目录下的scripts中
							③进入Python的安装目录下
							④python -m pip install numpy
				2.6.4、手动安装github包
							参考解决网址：https://blog.csdn.net/weixin_42277380/article/details/100521069
							①cd 打开到出现 setup.py 的文件目录 
							②shift + 鼠标右键，打开 Windows Powershell
							③输入命令 ： python setup.py install
		2.7、关于pycharm的配置
				2.7.1、工程文件夹解释器配置
						①python本身的解释器：
									C:\Users\chenbei\PycharmProjects\python学习工程文件夹\venv\Scripts\python.exe
						②工程文件夹的解释器：C:\Users\chenbei\PycharmProjects\python学习工程文件夹\venv\Scripts\python.exe
						③anconda的解释器：C:\Users\chenbei\anaconda3\python.exe
				2.7.2、模板文件配置
							①文件-设置-编辑器-文件和代码模板-Python Script---->
							②输入代码：
								#%%
								# -*- coding UTF-8 -*-
								'''
								@Project : ${PROJECT_NAME}
								@File : ${NAME}.py
								@Author : chenbei
								@Date : ${DATE} ${TIME}
								'''
								import matplotlib.pyplot as plt
								from matplotlib.pylab import mpl
								plt.rcParams['font.sans-serif'] = ['Times New Roman']  # 设置字体风格,必须在前然后设置显示中文
								mpl.rcParams['font.size'] = 10.5  # 图片字体大小
								mpl.rcParams['font.sans-serif'] = ['SimHei']  # 显示中文的命令
								mpl.rcParams['axes.unicode_minus'] = False  # 显示负号的命令
								mpl.rcParams['agg.path.chunksize'] = 10000
								plt.rcParams['figure.figsize'] = (7.8, 4.4)  # 设置figure_size尺寸
								plt.rcParams['savefig.dpi'] = 600  # 图片像素
								plt.rcParams['figure.dpi'] = 600  # 分辨率
								from matplotlib.font_manager import FontProperties
								font_set = FontProperties(fname=r"C:\Windows\Fonts\simsun.ttc", size=10.5)
								import numpy as np
								import pandas as pd
				2.7.3、科学模式配置
							视图--->Scientific Mode
				2.7.4、普通文件夹和包的区别
							包可以导入(不取中文名)，普通文件夹不能导入
				2.7.5、代码规范AutoPep8外部工具设置
							Program :  autopep8
							Arguments : --in-place --aggressive --aggressive $FilePath$
							Working diretory  : $ProjectFileDir$
							Output filters : $FILE_PATH$\:$LINE$\:$COLUMN$\:.*
<3>Qt的配置
		3.1、下载安装网站：http://download.qt.io/archive/qt/      下载，大概15分钟
		3.2、安装Qt时候的注意事项：安装必要的模块，参考书P6
				或者参考网址：https://blog.csdn.net/xue745146527/article/details/79405857
		3.3、pip3 install PyQt5 (此时仍然无法使用)
		还需安装PyQt5-Sip、PyQt5-Qt
		3.4、pycharm配置外部工具：
				参考网址：https://www.cnblogs.com/cthon/p/9379883.html
				文件-设置-Tools(工具)-External Tools(外部工具)
						Name :  取名
						Description :  描述 可以不填
						Program : 填写designer.exe的路径  对于本电脑的路径为 : 
										C:\Qt\Qt5.14.2\Tools\QtCreator\bin\qtcreator.exe
						Working diretory  : C:\Qt\Qt5.14.2\Tools\QtCreator\bin
		3.5、配置PyUIC : 用于编译ui文件为python文件
				3.5.1、手动编译步骤
							①cd到ui文件所在文件夹
							cd C:\Users\chenbei\Documents\pythonProjects\PYQT5_UI文件夹\Demo9\QMyListWidget
							pyuic5 -o QMyListWidget.py QMyListWidget.ui
							②资源文件需要到上级文件夹进行编译
							cd C:\Users\chenbei\Documents\pythonProjects\PYQT5_UI文件夹\Demo9
							pyrcc5 .\QMyListWidget\QMyListWidget.qrc -o QMyListWidgetn_rc.py
				3.5.2、外部工具编译
							参考方案  : https://blog.csdn.net/xuelanlingying/article/details/72963450
							Name : PyUIC
							Program :  C:\Users\chenbei\AppData\Local\Programs\Python\Python37\python.exe
							Arguments : -m PyQt5.uic.pyuic  $FileName$ -o $FileNameWithoutExtension$.py
							Working diretory :   ui文件存放的文件夹)
									C:\Users\chenbei\PycharmProjects\python学习工程文件夹 
		3.6、设置环境变量
		名称：QT_PLUGIN_PATH
		地址：python的包下Qt的plugins文件夹
				C:\Users\chenbei\AppData\Local\Programs\Python\Python37\Lib\site-packages\PyQt5\Qt\plugins
		3.7、复制plugins文件夹到Qt的编译器mingw下的bin文件夹下，重启pycharm即可
				C:\Qt\Qt5.14.2\5.14.2\mingw73_64\bin
				参考解决方案网址：https://blog.csdn.net/qq_37633082/article/details/100565144
<4>如何打包文件
		4.1、先到打包文件的所在文件夹
				cd C:\Users\chenbei\Desktop\2021.1.30备份\pyinstaller打包文件
		4.2、准备好图标文件16×16
		①打包命令1：pyinstaller -F girlfriend.py
				缺点是终端和运行文件一并产生，同时不能打包使用自己的图标
		②打包命令2 ： pyinstaller -i cake.ico -F  girlfriend.py
				可以打包自定义的图标，但是仍然会产生终端
		③打包命令3：pyinstaller -F -w girlfriend.py   没有终端但是不指定图标
		④打包命令4(推荐使用) : pyinstaller -F -w --icon=cake.ico girlfriend.py
<5>anconda3
		5.1、卸载包 ： 打开anconda的虚拟终端
				常用命令：
							conda list
							conda remove keras-proprocessing  移除安装包
<6>jupyter notebook  ： 生成ipynb文件