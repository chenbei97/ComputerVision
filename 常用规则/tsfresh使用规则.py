#%%
'''备忘录'''
'''C:/Users\chenbei\PycharmProjects\python学习工程文件夹\venv\Lib\site-packages\tsfresh\examples\data'''
'''
tsfresh数据集地址目录：
C:/Users\chenbei\Documents\python数据\tsfresh数据集
把目录下所有文件放入
C:/Users\chenbei\PycharmProjects\python学习工程文件夹\venv\Lib\site-packages\tsfresh\examples\data
数据下载地址为：
https://archive.ics.uci.edu/ml/datasets/Robot+Execution+Failures
解释博客为：
https://blog.csdn.net/zhouchen1998/article/details/88773929?utm_medium=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-2.channel_param&depth_1-utm_source=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-2.channel_param'''



''' 主要参数说明：
最重要的2个参数：
1、column_id ：此列指示时间序列所属的实体。 将为每个实体（id）分别提取要素，生成的特征矩阵将每个id包含一行。
 每个机器人都是不同的实体，因此每个机器人都有不同的ID
2、column_sort ：该列包含允许对时间序列进行排序的值（例如时间戳）。 通常，对于不同的id和/或种类，不需要等距的时间步长或相同的时标。 
但是，某些功能可能仅对等距时间戳有意义。 如果省略此列，则假定DataFrame已按升序排序
只需要某些格式指定的参数：
通过在tsfresh.extract_features（）函数中指定或不指定参数column_value和column_kind来指示flat DaraFrame和stack DataFrame之间的差异
如果column_value和column_kind都设置为None，则假定时间序列数据在flat DataFrame中，这意味着每个不同的时间序列必须另存为自己的列
1、column_value ：该列包含时间序列的实际值， 这对应于机器人上不同传感器的测量值
2、column_kind ：此列指示不同时间序列类型的名称（例如，工业应用中的不同传感器，如机器人数据集中的传感器）。 
对于每种时间序列，分别计算特征。
'''


'''tsfresh要求的数据格式有3种，现说明如下'''
'''
1、格式1：flat DataFrame(column_id="id", column_sort="time", column_kind=None, column_value=None)
包括在三个不同的时间t1，t2和t3的不同对象A和B的时间序列x和y的值
------------------------------------------------------
|     id     |     time     |     x     |     y     |
|     A      |     t1       |  x(A,t1)  |  y(A,t1)  |
|     A      |     t2       |  x(A,t2)  |  y(A,t2)  |  
|     A      |     t3       |  x(A,t3)  |  y(A,t3)  |
|     B      |     t1       |  x(B,t1)  |  y(B,t1)  |
|     B      |     t2       |  x(B,t2)  |  y(B,t2)  |
|     B      |     t3       |  x(B,t3)  |  y(B,t3)  |
------------------------------------------------------
2、格式2：Stacked DataFrame(column_id="id", column_sort="time", column_kind="kind", column_value="value")
如果同时设置了column_value和column_kind，则将时间序列数据假定为stack DataFrame。 
这意味着不同类型的时间序列没有不同的列。 与flat DataFrame相比，此表示具有多个优点：例如，不同时间序列的时间戳不必对齐。
id列决定分布 ：所有id一致的放在一起 ； 其次 kind追随id，先后顺序为x ，y
------------------------------------------------------
|     id     |     time     |    kind   |   value   |
|     A      |     t1       |     x     |  x(A,t1)  |
|     A      |     t2       |     x     |  x(A,t2)  |  
|     A      |     t3       |     X     |  x(A,t3)  |
|     A      |     t1       |     y     |  y(A,t1)  |
|     A      |     t2       |     y     |  y(A,t2)  |
|     A      |     t3       |     y     |  y(A,t3)  |
|     B      |     t1       |     x     |  x(B,t1)  |
|     B      |     t2       |     x     |  x(B,t2)  |  
|     B      |     t3       |     X     |  x(B,t3)  |
|     B      |     t1       |     y     |  y(B,t1)  |
|     B      |     t2       |     y     |  y(B,t2)  |
|     B      |     t3       |     y     |  y(B,t3)  |
------------------------------------------------------
注： 第1种和第2种本质上没有区别，只是从平铺式每列作为特征改为纵向特征，并添加kind指定标签
3、格式3 ： Dictionary of flat DataFrames(column_id="id", column_sort="time", column_kind=None, column_value="value")
字典映射，每种时间特征序列都使用单个DataFrame作为描述
特征列决定分布：将特征一致的变成同一个DataFrame ； 其次按id分布，先A后B
------------------------------------------------------
{"x":
|     id     |     time     |   value   |
|     A      |     t1       |  x(A,t1)  |
|     A      |     t2       |  x(A,t2)  |  
|     A      |     t3       |  x(A,t3)  |
|     B      |     t1       |  x(B,t1)  |
|     B      |     t2       |  x(B,t2)  |
|     B      |     t3       |  x(B,t3)  |
"y":
|     id     |     time     |   value   |
|     A      |     t1       |  y(A,t1)  |
|     A      |     t2       |  y(A,t2)  |  
|     A      |     t3       |  y(A,t3)  |
|     B      |     t1       |  y(B,t1)  |
|     B      |     t2       |  y(B,t2)  |
|     B      |     t3       |  y(B,t3)  |
-----------------------------------------------------
'''


'''tsfresh.feature_extraction.feature_calculators 说明'''
'''此模块包含功能计算器，这些功能计算器将时间序列作为输入并计算功能值'''
'''以下详尽列表包含在tsfresh当前版本中计算的所有功能'''
'''
--------------------------------------------------------------------------------------------------------------------------------------------------------
------------------------------------------1~15-------------------------------------------------------------------------------------------------------------
|  1  |       abs_energy(x)                                                    |  时间序列的绝对能量        
|  2  |       absolute_sum_of_changes(x)                                       |  对系列x的连续变化的绝对值求和
|  3  |       agg_autocorrelation(x, param)                                    |  计算聚合函数的值
|  4  |       agg_linear_trend(x, param)                                       |  块上聚合的时间序列值与从0到块数减一的序列的线性最小二乘回归
|  5  |       approximate_entropy(x, m, r)                                     |  矢量化的近似熵算法
|  6  |       ar_coefficient(x, param)                                         |  自回归AR（k）过程的无条件最大可能性
|  7  |       augmented_dickey_fuller(x, param)                                |  增强Dickey-Fuller检验是一种假设检验，用于检查时间序列样本中是否存在单位根
|  8  |       autocorrelation(x, lag)                                          |  计算指定滞后的自相关       
|  9  |       benford_correlation(x)                                           |  对于异常检测应用很有用
|  10 |       binned_entropy(x, max_bins)                                      |  首先将x的值合并到max_bins等距合并中
|  11 |       c3(x, lag)                                                       |                 ***
|  12 |       change_quantiles(x, ql, qh, isabs, f_agg)                        |  固定由x分布的分位数ql和qh给定的走廊
|  13 |       cid_ce(x, normalize)                                             |  该函数计算器是对时间序列复杂度的估计（更复杂的时间序列具有更多的峰，谷等）
|  14 |       count_above(x, t)                                                |  返回x中大于t的值的百分比
|  15 |       count_above_mean(x)                                              |  返回x中高于x均值的值的数量
|  16 |       count_below(x, t)                                                |  返回x中小于t的值的百分比       
------------------------------------------17~31-----------------------------------------------------------------------------------------------------------
|  17 |       count_below_mean(x)                                              |  返回x中小于x均值的值的数量
|  18 |       cwt_coefficients(x, param)                                       |  计算Ricker小波（也称为“墨西哥帽小波”）的连续小波变换
|  19 |       energy_ratio_by_chunks(x, param)                                 |  计算N个块中块i的平方和，以与整个系列的平方和之比表示
|  20 |       fft_aggregated(x, param)                                         |  返回绝对傅立叶变换频谱的频谱质心（均值），方差，偏度和峰度
|  21 |       fft_coefficient(x, param)                                        |  快速计算实际输入的一维离散傅立叶变换的傅立叶系数
|  22 |       first_location_of_maximum(x)                                     |  返回x最大值的第一个位置
|  23 |       first_location_of_minimum(x)                                     |  返回x最小值的第一个位置             
|  24 |       fourier_entropy(x, bins)                                         |  计算时间序列功率谱密度的装箱熵（使用韦尔奇方法）
|  25 |       friedrich_coefficients(x, param)                                 |  已拟合的多项式系数
|  26 |       has_duplicate(x)                                                 |  检查x中的任何值是否多次出现
|  27 |       has_duplicate_max(x)                                             |  检查是否多次观察到x的最大值
|  28 |       has_duplicate_min(x)                                             |  检查是否多次观察到x的最小值
|  29 |       index_mass_quantile(x, param)                                    |  这些应用特征计算相对指数i，其中时间序列x质量的q％位于i的左侧
|  30 |       kurtosis(x)                                                      |  返回x的峰度（使用调整后的Fisher-Pearson标准化矩系数G2计算）                         
|  31 |       large_standard_deviation(x, r)                                   |  布尔变量，表示x的标准dev是否高于“ r”乘以范围= x的最大值和最小值之间的差
---------------------------------------------32~46------------------------------------------------------------------------------------------------------
|  32 |       last_location_of_maximum(x)                                      |  返回x最大值的相对最后位置
|  33 |       last_location_of_minimum(x)                                      |  返回x最小值的相对最后位置
|  34 |       lempel_ziv_complexity(x, bins)                                   |  根据Lempel-Ziv压缩算法计算复杂度估算值
|  35 |       length(x)                                                        |  返回x的长度
|  36 |       linear_trend(x, param)                                           |  计算时间序列的值相对于从0到时间序列的长度减去1的序列的线性最小二乘回归
|  37 |       linear_trend_timewise(x, param)                                  |  计算时间序列值与从0到时间序列长度减去1的序列的线性最小二乘回归                    
|  38 |       longest_strike_above_mean(x)                                     |  返回x中最长的连续子序列的长度，该长度大于x的平均值
|  39 |       longest_strike_below_mean(x)                                     |  返回x中最长的连续子序列的长度，该长度小于x的平均值
|  40 |       max_langevin_fixed_point(x, r, m)                                |  动态最大固定点：math：argmax_x {h（x）= 0}`由多项式估算
|  41 |       maximum(x)                                                       |  计算时间序列x的最大值
|  42 |       mean(x)                                                          |  返回x的平均值
|  43 |       mean_abs_change(x)                                               |  返回后续时间序列值之间的绝对差的平均值
|  44 |       mean_change(x)                                                   |  返回后续时间序列值之间的差的平均值                                          
|  45 |       mean_second_derivative_central(x)                                |  返回二阶导数的中心近似值的平均值
|  46 |       median(x)                                                        |  返回x的中位数
--------------------------------------------47~62------------------------------------------------------------------------------------------------------
|  47 |       minimum(x)                                                       |  计算时间序列x的最小值
|  48 |       number_crossing_m(x, m)                                          |  计算x在m上的交叉数
|  49 |       number_cwt_peaks(x, n)                                           |  此功能计算器搜索x中的不同峰
|  50 |       number_peaks(x, n)                                               |  计算时间序列x中至少支持n的峰数
|  51 |       partial_autocorrelation(x, param)                                |  计算给定滞后下的部分自相关函数的值
|  52 |       percentage_of_reoccurring_datapoints_to_all_datapoints(x)        |  返回非唯一数据点的百分比  
|  53 |       percentage_of_reoccurring_values_to_all_values(x)                |  返回多次出现在时间序列中的值的百分比          
|  54 |       permutation_entropy(x, tau, dimension)                           |  计算置换熵
|  55 |       quantile(x, q)                                                   |  计算x的q分位数
|  56 |       range_count(x, min, max)                                         |  在间隔[min，max）内计数观察值
|  57 |       ratio_beyond_r_sigma(x, r)                                       |  距离x均值大于r * std（x）（r r sigma）的值的比率
|  58 |       ratio_value_number_to_time_series_length(x)                      |  如果时间序列中的所有值仅出现一次，则返回因子1，如果不是，则返回小于1的因子
|  59 |       sample_entropy(x)                                                |  计算并返回x的样本熵
|  60 |       set_property(key, value)                                         |  此方法返回一个装饰器，该装饰器将函数的属性键设置为value
|  61 |       skewness(x)                                                      |  返回x的样本偏度（使用调整后的Fisher-Pearson标准化矩系数G1计算）
|  62 |       spkt_welch_density(x, param)                                     |  该特征计算器估计不同频率下时间序列x的交叉功率谱密度
------------------------------------------63~72---------------------------------------------------------------------------------------------------------
|  63 |       standard_deviation(x)                                            |  返回x的标准偏差            
|  64 |       sum_of_reoccurring_data_points(x)                                |  返回时间序列中不止一次出现的所有数据点的总和
|  65 |       sum_of_reoccurring_values(x)                                     |  返回时间序列中多次出现的所有值的总和
|  66 |       sum_values(x)                                                    |  计算时间序列值的总和
|  67 |       symmetry_looking(x, param)                                       |  布尔变量，表示x的分布是否对称
|  68 |       time_reversal_asymmetry_statistic(x, lag)                        |                  ***
|  69 |       value_count(x, value)                                            |  计算时间序列x中值的出现次数
|  70 |       variance(x)                                                      |  返回x的方差
|  71 |       variance_larger_than_standard_deviation(x)                       |  布尔变量，表示x的方差是否大于其标准偏差           
|  72 |       variation_coefficient(x)                                         |  返回x的变化系数（标准误差/平均值，给出平均值附近变化的相对值）
---------------------------------------------------------------------------------------------------------------------------------------------------------
'''
#%%
import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
from pycaret.classification import *
from tsfresh import extract_relevant_features
from tsfresh.examples.robot_execution_failures import download_robot_execution_failures, \
    load_robot_execution_failures
'''导入数据'''
download_robot_execution_failures()
timeseries, y = load_robot_execution_failures()
timeseries[timeseries['id'] == 3].plot(subplots=True, sharex=True, figsize=(10,10))
plt.show()
features_filtered_direct = extract_relevant_features(timeseries, y,column_id='id', column_sort='time')
#提取特征后 为 88 行 626列 ，也就是每个故障有626个参数
features_filtered_direct['target'] = y
data = features_filtered_direct
for i in range(len(data.values[:,-1])):
    if str(data.iloc[i,-1]) == 'True':
        data.iloc[i,-1] = 1
    else:
        data.iloc[i,-1] = 0
'''比较模型进行选择'''
clf = setup(data = data , target = 'target')
#best = compare_models()
'''观察随机森林模型更好'''
RF = create_model(estimator= 'rf')
'''校准模型'''
calibrated_RF = calibrate_model(RF,method= 'sigmoid',fold= 10,verbose= True ,round=4 )
'''生成预测模型'''
pre = predict_model(calibrated_RF,platform= None,authentication= None) #data有88行，交叉验证法88*0.3=27行
'''预测其他数据的准备工作'''
pre_final = finalize_model(calibrated_RF) #参数还是calibrated_RF，而不是pre ，pre是个生成好的模型，不能作为参数
'''预测自身'''
Pre = predict_model(pre_final ,data=data,probability_threshold= None,platform= None ,authentication=None,verbose= None) #88行全预测了
'''自身预测的准确率'''
j = 0
for i in range(len(Pre.values[:,-3])):
    if Pre.values[i,-3] == Pre.values[i,-2]:
        j = j + 1
print('预测准确率为：'+ str(j/len(Pre.values[:,-3])*100) + '%')



