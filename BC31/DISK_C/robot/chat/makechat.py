import requests as req
import urllib as ul
import re

def qingyunke(msg):
    url='http://api.qingyunke.com/api.php?key=free&appid=0&msg={}'.format(ul.parse.quote(msg))
    html=req.get(url)
    return html.json()["content"]

inp=[]
for l in open("quest.txt","r",encoding='utf-8') :
    inp.append(l)
f=open("match.txt","w",encoding='gbk')
f=open("match.txt","a",encoding='gbk')
for i in range(len(inp)) :
    oup=qingyunke(inp[i])
    oup=oup+'\n'
    oup=re.sub(u"{.*?}","",oup)
    f.write(inp[i])
    f.write(oup)
print("Finish answered, answer: %d" % len(inp))