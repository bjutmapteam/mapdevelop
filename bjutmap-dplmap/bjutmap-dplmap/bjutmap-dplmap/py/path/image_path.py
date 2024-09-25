import cv2
import json
import os
import numpy as np
import math

# 使用绝对路径加载 buildings_data.json 文件
json_file_path = 'E:/bjutmap/schoolmapteam/py/buildings_data.json'

# 从 JSON 文件加载建筑物数据
with open(json_file_path, 'r', encoding='utf-8') as f:
    data = json.load(f)

# 提取建筑物数据到字典中，键是建筑物名称，值是坐标
buildings = {building['name']: building['position'] for building in data}

# 保存建筑物名称和路径信息
selected_buildings = []  # 用于存储点击的建筑物名称
paths = []  # 用于存储连接的路径信息

# 缩放相关变量
scale_factor = 0.5  # 初始缩放比例设为 0.5，展示完整地图
min_scale = 0.2     # 允许的最小缩放比例
max_scale = 2.0     # 允许的最大缩放比例

# 平移相关变量
dragging = False
start_x, start_y = 0, 0
offset_x, offset_y = 0, 0

# 调试路径是否正确
image_path = 'E:/bjutmap/bjutmap.jpg'
if not os.path.exists(image_path):
    print(f"文件路径 {image_path} 不存在，请检查路径是否正确。")
else:
    print(f"文件路径 {image_path} 存在，继续加载图像...")

# 加载地图图像
original_image = cv2.imread(image_path)

# 定义计算像素距离的函数
def calculate_distance(building1, building2):
    x1, y1 = buildings[building1]
    x2, y2 = buildings[building2]
    distance = math.sqrt((x2 - x1) ** 2 + (y2 - y1) ** 2)
    return distance

# 定义鼠标回调函数，处理点击、滚轮缩放和右键拖动
def mouse_event(event, x, y, flags, param):
    global scale_factor, dragging, start_x, start_y, offset_x, offset_y, image, selected_buildings, paths  # 添加 paths

    # 处理鼠标左键点击事件（用于选择建筑物）
    if event == cv2.EVENT_LBUTTONDOWN:
        for building_name, position in buildings.items():
            px, py = position
            px_scaled = int(px * scale_factor + offset_x)
            py_scaled = int(py * scale_factor + offset_y)
            distance = ((px_scaled - x) ** 2 + (py_scaled - y) ** 2) ** 0.5
            if distance < 20:  # 点击的点在建筑物附近
                selected_buildings.append(building_name)
                print(f"选中了建筑物: {building_name}")

                # 如果选择了两个建筑物，绘制连接线并记录路径和距离
                if len(selected_buildings) == 2:
                    building1, building2 = selected_buildings
                    distance_between_buildings = calculate_distance(building1, building2)
                    paths.append({
                        "from": building1,
                        "to": building2,
                        "distance": distance_between_buildings  # 记录建筑物之间的距离
                    })
                    # 绘制路径
                    cv2.line(image, 
                             (int(buildings[building1][0] * scale_factor + offset_x), 
                              int(buildings[building1][1] * scale_factor + offset_y)),
                             (int(buildings[building2][0] * scale_factor + offset_x), 
                              int(buildings[building2][1] * scale_factor + offset_y)),
                             (0, 255, 0), 2)
                    cv2.imshow("Map", image)
                    print(f"已连接 {building1} 到 {building2}，距离为 {distance_between_buildings:.2f} 米")
                    selected_buildings = []  # 重置选择

    # 处理鼠标滚轮缩放事件
    elif event == cv2.EVENT_MOUSEWHEEL:
        if flags > 0:  # 向上滚动，放大
            scale_factor = min(scale_factor * 1.1, max_scale)
        else:  # 向下滚动，缩小
            scale_factor = max(scale_factor * 0.9, min_scale)

        # 缩放图像并重新绘制路径和建筑物
        redraw_image()

    # 处理鼠标右键按下开始拖动
    elif event == cv2.EVENT_RBUTTONDOWN:
        dragging = True
        start_x, start_y = x, y  # 记录起始位置

    # 处理鼠标右键拖动
    elif event == cv2.EVENT_MOUSEMOVE and dragging:
        dx = x - start_x
        dy = y - start_y
        offset_x += dx
        offset_y += dy

        # 限制平移范围，确保不出现黑色背景
        max_offset_x = int(original_image.shape[1] * scale_factor) - image.shape[1]
        max_offset_y = int(original_image.shape[0] * scale_factor) - image.shape[0]
        offset_x = min(max(offset_x, -max_offset_x), 0)
        offset_y = min(max(offset_y, -max_offset_y), 0)

        start_x, start_y = x, y  # 更新起始点

        # 重新绘制图像，带有平移
        redraw_image()

    # 处理鼠标右键释放，停止拖动
    elif event == cv2.EVENT_RBUTTONUP:
        dragging = False

# 重新绘制图像及建筑物和路径
def redraw_image():
    global image, offset_x, offset_y, scale_factor

    # 缩放图像
    new_size = (int(original_image.shape[1] * scale_factor), int(original_image.shape[0] * scale_factor))
    resized_image = cv2.resize(original_image, new_size)

    # 创建一个黑色背景图像
    image = np.zeros((int(original_image.shape[0] * scale_factor), 
                      int(original_image.shape[1] * scale_factor), 3), dtype=np.uint8)

    # 将缩放后的图像根据偏移量绘制到黑色背景上
    x_start = max(0, offset_x)
    y_start = max(0, offset_y)
    img_x_start = max(0, -offset_x)
    img_y_start = max(0, -offset_y)

    img_x_end = min(image.shape[1], img_x_start + resized_image.shape[1])
    img_y_end = min(image.shape[0], img_y_start + resized_image.shape[0])

    if img_x_end > img_x_start and img_y_end > img_y_start:
        image[y_start: y_start + (img_y_end - img_y_start),
              x_start: x_start + (img_x_end - img_x_start)] = resized_image[img_y_start: img_y_end, img_x_start: img_x_end]

    # 绘制建筑物
    for building_name, position in buildings.items():
        # 计算建筑物相对位置
        scaled_position = (int(position[0] * scale_factor + offset_x), int(position[1] * scale_factor + offset_y))
        cv2.circle(image, scaled_position, 5, (0, 0, 255), -1)
        cv2.putText(image, building_name, (scaled_position[0] + 15, scaled_position[1] - 10), 
                    cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 0, 0), 2)

    # 绘制路径
    for path in paths:
        building1, building2 = path["from"], path["to"]
        cv2.line(image, 
                 (int(buildings[building1][0] * scale_factor + offset_x), 
                  int(buildings[building1][1] * scale_factor + offset_y)),
                 (int(buildings[building2][0] * scale_factor + offset_x), 
                  int(buildings[building2][1] * scale_factor + offset_y)),
                 (0, 255, 0), 2)

    # 显示更新后的图像
    cv2.imshow("Map", image)

# 确认图像是否正确加载
if original_image is None:
    print("无法加载图像，请检查路径。")
else:
    print("图像加载成功。")
    image = original_image.copy()

    # 显示所有建筑物的位置和名称
    redraw_image()

    # 绑定鼠标点击、滚轮缩放和右键拖动事件
    cv2.setMouseCallback("Map", mouse_event)

    # 按任意键退出程序
    cv2.waitKey(0)

    # 关闭所有窗口
    cv2.destroyAllWindows()

# 将路径保存到 JSON 文件
json_data = {
    "buildings": [{"name": name, "position": position} for name, position in buildings.items()],
    "paths": paths
}

# 保存路径和建筑物信息到 JSON 文件
with open('map_data_with_paths.json', 'w', encoding='utf-8') as f:
    json.dump(json_data, f, ensure_ascii=False, indent=4)

print("路径数据已保存到 map_data_with_paths.json")
