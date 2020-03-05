import requests
from lxml import etree

#伪装成浏览器
headers = {"User-Agent":"Mozilla/5.0 (Windows NT 6.1) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/63.0.3239.84 Safari/537.36"}

url_tmp = "http://www.paoshu8.com/0_108/73500.html"

ret_data = requests.get(url_tmp, headers = headers)

#将服务器返回的html文件 转换成一棵DOM树
html = etree.HTML(ret_data.content.decode())
#通过xpath方法查找DOM树下的结点
#找到class属性为"bookname"的div标签下的所有的p标签
#注意：xpath返回的结果是个列表
lis = html.xpath('//div[@class="bookname"]//p')
#爬取到第几章的小说内容
for x in range(4):
    for li in lis:
        print(li.text)
    #找到下一章的标签
    next = html.xpath('//div[@class="bookname"]//a')[3]
    #取出下一章网站
    url_tmp = "http://www.paoshu8.com/" + next.attrib.get("href")
    #访问该网址
    ret_data = requests.get(url_tmp, headers = headers)
    #将服务器返回的html文件 转换成一棵DOM树
    html = etree.HTML(ret_data.content.decode())
    lis = html.xpath('//div[@class="bookname"]//p')