/*
<1>需求
		1. 12人参加比赛 第一轮淘汰赛 第二轮决赛
		2. 每名选手有编号 如10001~10012
		3. 分组比赛 ，组6人
		4. 第一轮2个小组，整天按照选手编号进行抽签后顺序演讲
		5. 十个评委打分，去除最高最低分，求平均分
		6. 每组前三名晋级进入下一轮
		7. 决赛前3名胜出
		8. 每轮比赛过后显示晋级选手信息
<2>功能
		1. 开闭演讲比赛，完成流程，每个比赛阶段给用户提示 ，用户按任意键继续下一个阶段
		2. 查看往届记录：查看之前比赛的前三名，每次比赛记录到文件，文件名用csv保存
		3. 清空比赛记录
		4. 退出比赛程序
<3> 比赛流程分析
		1. 抽签->淘汰赛->显示第一轮结果->
		2. 抽签->决赛->显示前3名结果->保存分数->更新初始化的状态
*/