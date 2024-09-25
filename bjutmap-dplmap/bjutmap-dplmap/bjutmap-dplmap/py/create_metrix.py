import json
import numpy as np

# 从 JSON 文件中加载数据
with open('map_data_with_paths.json', 'r', encoding='utf-8') as file:
    data = json.load(file)

# 获取建筑物名字列表
buildings = [building["name"] for building in data["buildings"]]
n = len(buildings)

# 初始化邻接矩阵
adj_matrix = np.full((n, n), np.inf)

# 设置对角线为 0
np.fill_diagonal(adj_matrix, 0)

# 为路径填充邻接矩阵
for path in data["paths"]:
    i = buildings.index(path["from"])
    j = buildings.index(path["to"])
    adj_matrix[i][j] = int(round(path["distance"]))
    adj_matrix[j][i] = int(round(path["distance"]))  # 假设路径是双向的

# 将矩阵中的非无穷大值转换为整数
adj_matrix = np.where(np.isinf(adj_matrix), 'INF', adj_matrix.astype(int))

# 自定义格式输出矩阵
output = "{\n"
for row in adj_matrix:
    row_str = ', '.join(map(str, row))
    output += f"\t{{{row_str}}},\n"
output = output.rstrip(',\n') + "\n};"  # 移除最后一个逗号并关闭大括号

# 将输出写入桌面的 matrix.txt 文件
desktop_path = 'C:/Users/86182/Desktop/matrix.txt'  # 修改为实际用户名
with open(desktop_path, 'w', encoding='utf-8') as file:
    file.write("邻接矩阵：\n")
    file.write(output)

print("矩阵已成功写入桌面的 matrix.txt 文件。")
