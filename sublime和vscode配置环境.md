<1>下载地址
	https://www.sublimetext.com/3
<2>汉化
	2.1、使用快捷键Shift+Ctrl+P,弹出查找栏
	2.2、搜索框中输入关键字 install ,出现下拉选项，点击选择其中的：Package Control: Install Package
	2.3、在搜索框中输入chinese，选择下拉框中的ChineseLocalizations
	2.4、解决方案地址：https://blog.csdn.net/qq_43722079/article/details/97777585?utm_medium=distribute.pc_relevant.none-task-blog-BlogCommendFromBaidu-2.control&depth_1-utm_source=distribute.pc_relevant.none-task-blog-BlogCommendFromBaidu-2.control
<3>配置python编译环境
	3.0、解决方案地址 : 
	(1)https://www.cnblogs.com/haoprogrammer/p/8284908.html
	3.1、设置编码和字体 : 
	 		首选项----->设置
	 		左方设置 : 
					"font_size": 14,
					"default_encoding":"UTF-8",
					"tab_size":4,
			右方设置 : 
			{
				"color_scheme": "Packages/Theme - Spacegray/base16-ocean.dark.tmTheme",
				"default_encoding": "UTF-8",
				"font_face": "Times New Roman",
				"font_size": 14,
				"ignored_packages":
				[
				"Vintage"
				],
				"tab_size": 4,
				"theme": "Adaptive.sublime-theme"
			}
	3.2、配置解释器
			工具--->编译系统--->新建编译系统
					默认的文件内容 : 
							{
								"shell_cmd": "make"
							}
					将其改设置为 :  其中cmd是python解释器 保存即生成python_interpreter.sublime-build文件
							{
							"encoding": "GBK",  
						    "working_dir": "$file_path",
						    "file_regex": "^[ ]*File \"(...*?)\", line ([0-9]*)",  
						    "selector": "source.python" ,
							"cmd": "C:\\Users\\chenbei\\PycharmProjects\\python学习工程文件夹\\venv\\Scripts\\python.exe -u \"$file\"",
							}
	3.3、解决中文乱码问题 : 
		https://blog.csdn.net/qq122261257/article/details/8585285?utm_medium=distribute.pc_relevant.none-task-blog-OPENSEARCH-14.control&depth_1-utm_source=distribute.pc_relevant.none-task-blog-OPENSEARCH-14.control
		下载ConvertToUTF8即可
<4>配置C++编译环境
	4.1、配置C ++编辑器
			4.1.1、解决方案
					https://blog.csdn.net/shenwanjiang111/article/details/53728941?utm_medium=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-6.control&dist_request_id=0a476012-d5cf-4a3c-85f2-5d5d9981444d&depth_1-utm_source=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-6.control
			4.1.2、新建编译系统写入内容如下 : 
					{
						//"shell_cmd": "make"
						"encoding": "utf-8",
					    "working_dir": "$file_path",
					    "shell_cmd": "g++ -Wall -std=c++0x \"$file_name\" -o \"$file_base_name\"",
					    "file_regex": "^(..[^:]*):([0-9]+):?([0-9]+)?:? (.*)$",
					    "selector": "source.cpp",
					    "variants": 
					    [
					        {   
					        "name": "Run",
					            "shell_cmd": "g++ -Wall -std=c++0x  \"$file\" -o \"$file_base_name\" && \"${file_path}/${file_base_name}\""
					        },
					        {   
					        "name": "RunInCmd",
					            "shell_cmd": "g++ -Wall -std=c++0x  \"$file\" -o \"$file_base_name\" && start cmd /c \"\"${file_path}/${file_base_name}\" & pause \""
					        }
					    ]
					}
<5>下载编译器(vscode用到 sublime似乎没用到)
		5.1、下载地址
			mingw64下载地址: https://pan.baidu.com/s/1_gdaid7yvGTqN2xikoEUmQ  密码 : ne84
			cmake下载地址  : https://cmake.org/download/
			vscode下载地址 : https://code.visualstudio.com
			解决方案地址 : https://www.bilibili.com/video/BV1sW411v7VZ?from=search&seid=4221066227845347372
		5.2、配置环境
				5.2.1、应用商店安装C++插件
				5.2.2、环境变量设置
						1、用户变量 :  C:\VSCode\Microsoft VS Code\bin （vsvode的安装bin文件目录）
						2、系统变量 :  C:\mingw64\bin   (mingw64的bin文件目录)
		5.3、在vscode文件夹下新建hello文件夹
				5.3.1、hello文件夹再新建hello.cpp文件 点击编译创建launch.json文件会自动创建
						生成的编译文件 .\hello.exe 直接运行即可  如果重复编译会出现错误
				5.3.2、对于tasks文件也可以手动创建 ： ctrl + shift+ p 输入 ： >tasks:configure Task
				5.3.3、tasks.json文件需要添加的内容为  :  "-std=c++17" 
						"${fileDirname}\\${fileBasenameNoExtension}.exe",
                		"-std=c++17"
                5.3.4、launch.json文件设置
              			"externalConsole": false,
           				"internalConsoleOptions": "neverOpen",
        5.4、设置的改动
       			5.4.1、 格式规范设置：
       					设置--->拓展--->c/c++--->ClangFormt当中输入：{BaseOnStyle:LLVM,UseTab:Never,IndentWidth:4}
       			5.4.2、C++标准：选择c++20

