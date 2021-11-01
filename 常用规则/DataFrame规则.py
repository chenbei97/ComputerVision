#%%
import pandas as pd
import numpy as np
dat = pd.DataFrame(np.random.rand(4,8),columns= list('abcdefgh'))
#1、删除某列
del dat['h']
#2、排序
dat.sort_values("b",ascending=False,inplace=True) #ascending = False 表示降序
#3、检查每列缺失值，返回其个数
dat.isnull().sum()
#4、填充缺失值
#data = data.fillna(axis=0,method='ffill')
#5、去除重复值
dat.drop_duplicates(['a'],inplace=True)
#6、描述性统计
dat['c'].describe()
#7、数据可视化
dat['d'].hist()
#8、随机抽样sample
dat.sample(n=2,axis=1) #按列
#9、重设行标签
dat.index = ['01','02','03','04']
#10、重设列标签
dat.columns = ['0','1','2','3','4','5','6']
#11、更改指定行列标签名
dat.rename(columns={"4":"four"},index = {"02":"zero_two"},inplace=True ) #inplace必须为True，否则不改变原有值
#12、查看头部和尾部数据
# dat.head()
# dat.tail()
#13、索引
#13.1、按行号和列名索引
print(dat.loc['zero_two','four']) #参数为字符串
#13.2、按行号和列号索引
print(dat.iloc[1,4]) #参数为整数
#%%
#14、拼接函数
Dat = pd.concat([dat,dat],axis=0,ignore_index= True)  #按行
#15、交换两列位置，但是列名字没有交换
dat[['four','3']] = dat[['3','four']]
#16、遍历元素
for index ,row in dat.iterrows() : #返回值是元组
    print(index)
    print(row)
#17、找到某几列
#class_1 = data[['Alcohol','Ash']]
# 18、比较索引
d = pd.Series()
dat.index.isin(d.index)# 比较两个索引 相等为True  返回长度和dat相同



