from flask import Flask,render_template,request,url_for,redirect
import json
app = Flask(__name__)

Now_score = {"0000":"0","1111":"100","2222":"200","3333":"300"}
Now_Data = {"CarA":"A","ScoreA":"0","CarB":"B","ScoreB":"0"}

@app.route("/")
def index():
    return render_template("score.html",Now_Data = Now_Data,Now_score = Now_score)
@app.route("/register",methods = ['POST'])
def register():
    Car = request.form.get('Car')
    Name = request.form.get('Name')
    if Car == "A":
        Now_Data["CarA"] = Name
    else:
        Now_Data["CarB"] = Name
    return redirect('/')


@app.route("/scoreboard",methods = ['GET','POST'])
def test():
    if request.method == "POST":
        RFID = request.form.get('RFID')
        Car = request.form.get('Car')

        if Car == "A":
            score = scoreboard(RFID)
            Now_Data["ScoreA"] = str(int(Now_Data["ScoreA"])+int(score))
            return render_template("score.html",Now_Data = Now_Data,Now_score = Now_score)
        elif Car == "B":
            score = scoreboard(RFID)
            Now_Data["ScoreB"] = str(int(Now_Data["ScoreB"])+int(score))
            return render_template("score.html",Now_Data = Now_Data,Now_score = Now_score)
        else:
            return 'Error! There is no Car %s' %Car
    else:
        return redirect('/')
def scoreboard(RFID):
    if(Now_score[RFID]):
        s = Now_score[RFID]
        i = int(Now_score[RFID])
        i = i - 10
        Now_score[RFID] = str(i)
        return s
    else:
        return 0

@app.route('/getTable', methods = ['POST'])
def send():
    jsondata = request.get_json()
    Message = json.loads(jsondata)
    result = {'Now_score' : Now_score}
    return json.dumps(result)

if __name__ == '__main__':
    app.run(debug=True)