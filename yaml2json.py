import yaml
import json
import os

# yaml文件内容转换成json格式，需要pip install pyyaml
def yaml_to_json(yamlPath, name):
    with open(yamlPath +"\\" + name + ".yaml", encoding="utf-8") as f:
        datas = yaml.load(f,Loader=yaml.FullLoader)  # 将文件的内容转换为字典形式
    jsonDatas = json.dumps(datas, indent=5) # 将字典的内容转换为json格式的字符串
    # print(jsonDatas)
    f = open("C:/Users/CY/desktop/PJ_export/json/" + name +".json","w")
    f.write(jsonDatas)


yamlPath = r'C:\Users\CY\desktop\PJ_export\answer'
    
for root,dirs,files in os.walk(yamlPath):
    for file in files:
        print(file)
        yaml_to_json(yamlPath, os.path.splitext(file)[0])