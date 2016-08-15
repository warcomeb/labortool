import ConfigParser
from flask import Flask, jsonify, request
from flask_sqlalchemy import SQLAlchemy
import models

api = Flask(__name__)

#Read config file
config = ConfigParser.ConfigParser()  
config.read('db_config.conf')

#MySQL configurations
api.config['SQLALCHEMY_DATABASE_URI'] = 'mysql+mysqldb://' + config.get('DB', 'user') + ':' + config.get('DB', 'password') + '@' + config.get('DB', 'host') + '/' + config.get('DB', 'db')

api.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = True

mysql = SQLAlchemy(api)
#mysql.init_app(api)

@api.route('/inventory/manufacturer', methods=['POST'])
def createManufacturer():
    name = request.get_json()["Name"]
    webSite = request.get_json()["WebSite"]

    manufacturer = models.Manufacturer(Name = name, WebSite = webSite)

    curr_session = mysql.session
    try:
        curr_session.add(manufacturer)
        curr_session.commit()
    except:
        curr_session.rollback()
        curr_session.flush()

    data = models.Manufacturer.query.order_by(Manufacturer.Id.desc()).first()
    config.read('db_config.conf')
    result = [data.Id, data.Name, data.WebSite]

    return jsonify(session = result)