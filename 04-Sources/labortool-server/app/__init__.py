from flask import Flask
from flask_sqlalchemy import SQLAlchemy

app = Flask(__name__)                       #create the application object
app.config.from_object('config')            #importing the file configuration
db = SQLAlchemy(app)                        #creating the DB object

from app import views, models               #importing the views modules and models for DB
from flask import Flask, jsonify, abort, make_response, request, url_for

@app.errorhandler(400)
def NotFound(error):
    return make_response(jsonify( { 'error': 'Bad request!' } ), 400)

@app.errorhandler(404)
def NotFound(error):
    return make_response(jsonify({'error':'Not found'}), 404)

# start of GET ALL calls

@app.route('/getall/component', methods=['GET'])
def get_All_component():
    return jsonify({'Component': models.Component.query.all()})

@app.route('/getall/manufacturer', methods=['GET'])
def get_All_manufacturer():
    return jsonify({'Manufacturer': models.Manufacturer.query.all()})

@app.route('/getall/distributor', methods=['GET'])
def get_All_distributor():
    return jsonify({'Distributor': models.Distributor.query.all()})

@app.route('/getall/location', methods=['GET'])
def get_All_location():
    return jsonify({'Location': models.Location.query.all()})

@app.route('/getall/category', methods=['GET'])
def get_All_category():
    return jsonify({'Category': models.Category.query.all()})

@app.route('/getall/categoryparamtype', methods=['GET'])
def get_All_categoryparamtype():
    return jsonify({'CategoryParamType': models.CategoryParamType.query.all()})

@app.route('/getall/componentparam', methods=['GET'])
def get_All_componentparam():
    return jsonify({'ComponentParam': models.ComponentParam.query.all()})

@app.route('/getall/bomelement', methods=['GET'])
def get_All_bomelement():
    return jsonify({'BomElement': models.BomElement.query.all()})

@app.route('/getall/board', methods=['GET'])
def get_All_board():
    return jsonify({'Board': models.Board.query.all()})

@app.route('/getall/bom', methods=['GET'])
def get_All_bom():
    return jsonify({'Bom': models.Bom.query.all()})

@app.route('/getall/unit', methods=['GET'])
def get_All_unit():
    return jsonify({'Unit': models.Unit.query.all()})

@app.route('/getall/project', methods=['GET'])
def get_All_project():
    return jsonify({'Project': models.Project.query.all()})

# end of GET ALL calls

@app.route('/getdata/all/<int:data_id>', methods=['GET'])
def get_byId(data_id):
    singleData = [singleData for singleData in data if singleData['id'] == data_id]
    if len(singleData) == 0:
        abort(404)
    return jsonify({'singleData': singleData[0]})

@app.route('/postdata/all', methods=['POST'])
def create_data():
    if not request.json or not 'title' in request.json:
        abort(400)
    singleData = {
        'id': data[-1]['id'] + 1,
        'title': request.json['title'],
        'description': request.json.get('description', ""),
        'done': False
    }
    data.append(singleData)
    return jsonify({'singleData': singleData}), 201