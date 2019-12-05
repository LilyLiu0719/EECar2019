import requests
import json
import sys

a = requests
profile = {"Car" : "A", "Name" : "3-Min"}
b = a.post('http://127.0.0.1:5000/register', profile)


s = requests
data = {"RFID":"3333","Car":"A"}
eat = s.post('http://127.0.0.1:5000/scoreboard', data)

dump = [{'test':'test','ttt':'ttt'}]
q = json.dumps(dump)
res = requests.post("http://127.0.0.1:5000/getTable", json=q).json()
print("RFID Table")
print(res['Now_score'])

# print r.status_code
# print r.headers['content-type']
# print r.encoding
# print r.text