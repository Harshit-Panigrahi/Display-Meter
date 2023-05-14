from flask import Flask, request, render_template, jsonify
from firebase_admin import credentials, firestore, initialize_app
from key import creds

cert = credentials.Certificate(creds)
initialize_app(cert)
db = firestore.client()

app = Flask(__name__)

@app.route('/', methods=['GET'])
def index():
  try:
    doc_data = db.collection('Potentiometer').document('Values').get().to_dict()
    val = doc_data['value']
    return render_template('index.html' , reading = val)
  
  except Exception as e:
    return jsonify({
      "status": "error",
      "message": str(e)
    }), 400

@app.route('/add', methods=['POST'])
def addData():
  try:
    val = request.json.get('value')
    db.collection("Potentiometer").document("Values").set({ 'value': val })
    return jsonify({ "status": "success" }), 201

  except Exception as e:
    return jsonify({
      "status": "error",
      "message": str(e)
    }), 400

if __name__  ==  "__main__":
  app.run()
