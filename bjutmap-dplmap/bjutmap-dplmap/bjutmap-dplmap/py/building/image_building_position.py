import cv2
import json
import tkinter as tk
from tkinter import simpledialog

# 加载地图图像
image = cv2.imread('E:/bjutmap/bjutmap.jpg')

# 保存原始图像，用于缩放时还原
original_image = image.copy()

# 初始缩放比例
scale_factor = 1.0

# 记录鼠标右键按下时的位置
dragging = False
start_x, start_y = 0, 0

# 偏移量，用于平移图像
offset_x, offset_y = 0, 0

# 创建一个用于存储建筑物的列表
buildings = []

# 定义函数，用于根据偏移量裁剪图像
def get_display_image():
    h, w = image.shape[:2]
    display_image = cv2.resize(original_image, (int(w * scale_factor), int(h * scale_factor)))

    # 限制偏移量，确保图像不会超出边界
    max_x_offset = display_image.shape[1] - w
    max_y_offset = display_image.shape[0] - h

    offset_x_clamped = max(0, min(offset_x, max_x_offset))
    offset_y_clamped = max(0, min(offset_y, max_y_offset))

    # 根据偏移量裁剪图像
    cropped_image = display_image[offset_y_clamped:offset_y_clamped+h, offset_x_clamped:offset_x_clamped+w]
    return cropped_image

# 定义鼠标回调函数，处理点击、滚轮缩放和右键拖动
def mouse_event(event, x, y, flags, params):
    global scale_factor, image, dragging, start_x, start_y, offset_x, offset_y

    # 处理鼠标左键点击事件
    if event == cv2.EVENT_LBUTTONDOWN:  # 鼠标左键点击
        # 弹出输入框，输入建筑物名称
        root = tk.Tk()
        root.withdraw()  # 隐藏主窗口
        building_name = simpledialog.askstring("输入建筑物名称", f"请输入位于 ({x}, {y}) 的建筑物名称：")

        # 如果用户输入了名称，保存数据
        if building_name:
            # 将名称和像素位置记录到 buildings 列表中，保存为原始比例下的坐标
            buildings.append({
                "name": building_name,
                "position": [int((x + offset_x) / scale_factor), int((y + offset_y) / scale_factor)]
            })
            print(f"建筑物：{building_name}, 位置：x={x}, y={y}")

            # 在点击的地方标记红点
            cv2.circle(image, (x, y), 5, (0, 0, 255), -1)
            cv2.putText(image, building_name, (x + 10, y - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (255, 0, 0), 1)

            # 显示更新后的图像
            display_image = get_display_image()
            cv2.imshow("Map", display_image)

    # 处理滚轮缩放事件
    elif event == cv2.EVENT_MOUSEWHEEL:
        # 判断滚轮方向
        if flags > 0:  # 滚轮向前滚动（放大）
            scale_factor *= 1.1
        else:  # 滚轮向后滚动（缩小）
            scale_factor *= 0.9

        # 更新显示图像
        display_image = get_display_image()

        # 重新绘制已保存的标记
        for building in buildings:
            x_scaled = int(building['position'][0] * scale_factor - offset_x)
            y_scaled = int(building['position'][1] * scale_factor - offset_y)
            cv2.circle(display_image, (x_scaled, y_scaled), 5, (0, 0, 255), -1)
            cv2.putText(display_image, building["name"], (x_scaled + 10, y_scaled - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (255, 0, 0), 1)

        # 显示更新后的图像
        cv2.imshow("Map", display_image)

    # 处理鼠标右键按下开始拖动
    elif event == cv2.EVENT_RBUTTONDOWN:
        dragging = True
        start_x, start_y = x, y  # 记录起始位置

    # 处理鼠标移动（在右键按住时）
    elif event == cv2.EVENT_MOUSEMOVE and dragging:
        # 计算拖动的偏移量
        dx = x - start_x
        dy = y - start_y

        # 更新偏移量
        offset_x -= dx
        offset_y -= dy

        # 更新图像显示
        display_image = get_display_image()
        for building in buildings:
            x_scaled = int(building['position'][0] * scale_factor - offset_x)
            y_scaled = int(building['position'][1] * scale_factor - offset_y)
            cv2.circle(display_image, (x_scaled, y_scaled), 5, (0, 0, 255), -1)
            cv2.putText(display_image, building["name"], (x_scaled + 10, y_scaled - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (255, 0, 0), 1)

        cv2.imshow("Map", display_image)

        # 更新开始拖动位置
        start_x, start_y = x, y

    # 处理鼠标右键释放，停止拖动
    elif event == cv2.EVENT_RBUTTONUP:
        dragging = False

# 显示初始图像
cv2.imshow("Map", get_display_image())

# 绑定鼠标事件（点击、滚轮缩放和右键拖动）
cv2.setMouseCallback("Map", mouse_event)

# 按任意键退出程序
cv2.waitKey(0)

# 关闭所有窗口
cv2.destroyAllWindows()

# 将建筑物名称和位置保存到 JSON 文件，并确保中文正常显示
json_file = 'buildings_data.json'
with open(json_file, 'w', encoding='utf-8') as f:
    json.dump(buildings, f, ensure_ascii=False, indent=4)

print(f"建筑物数据已保存到 {json_file}")
