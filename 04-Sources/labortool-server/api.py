import ConfigParser
from datetime import timedelta
from flask_sqlalchemy import SQLAlchemy
from flask_restful import fields, marshal
from flask import Flask, jsonify, request, make_response, current_app
from functools import update_wrapper
<<<<<<< HEAD

api = Flask(__name__)

#### Begin on network configuration ####
def crossdomain(origin=None, methods=None, headers=None, max_age=21600, attach_to_all=True, automatic_options=True):
    if methods is not None:
        methods = ', '.join(sorted(x.upper() for x in methods))
    if headers is not None and not isinstance(headers, basestring):
        headers = ', '.join(x.upper() for x in headers)
    if not isinstance(origin, basestring):
        origin = ', '.join(origin)
    if isinstance(max_age, timedelta):
        max_age = max_age.total_seconds()

    def get_methods():
        if methods is not None:
            return methods

        options_resp = current_app.make_default_options_response()
        return options_resp.headers['allow']

    def decorator(f):
        def wrapped_function(*args, **kwargs):
            if automatic_options and request.method == 'OPTIONS':
                resp = current_app.make_default_options_response()
            else:
                resp = make_response(f(*args, **kwargs))
            if not attach_to_all and request.method != 'OPTIONS':
                return resp

            h = resp.headers

            h['Access-Control-Allow-Origin'] = origin
            h['Access-Control-Allow-Methods'] = get_methods()
            h['Access-Control-Max-Age'] = str(max_age)
            if headers is not None:
                h['Access-Control-Allow-Headers'] = headers
            return resp

        f.provide_automatic_options = False
        return update_wrapper(wrapped_function, f)
    return decorator
#### End of network configuration ####
=======
from flask_cors import CORS, cross_origin

api = Flask(__name__)
CORS(api)

>>>>>>> beta

#### Begin DB connection and configuration ####
config = ConfigParser.ConfigParser()  
config.read('db_config.conf')
api.config['SQLALCHEMY_DATABASE_URI'] = 'mysql+mysqldb://' + config.get('DB', 'user') + ':' + config.get('DB', 'password') + '@' + config.get('DB', 'host') + '/' + config.get('DB', 'db')
api.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = True
mysql = SQLAlchemy(api)
#### End of DB connection and configuration ####

##### Map models #####
# Manufacturer model
class Manufacturer(mysql.Model):  
    __tablename__ = 'manufacturer'
    Id = mysql.Column(mysql.Integer, primary_key=True)
    Name = mysql.Column(mysql.String(50), nullable=False)
    WebSite = mysql.Column(mysql.String(120), nullable=False)

    def __repr__(self):
        return '<Manufacturer (%s, %s) >' % (self.Name, self.WebSite)

# Distributor model
class Distributor(mysql.Model):  
    __tablename__ = 'distributor'
    Id = mysql.Column(mysql.Integer, primary_key=True)
    Name = mysql.Column(mysql.String(50), nullable=False)
    WebSite = mysql.Column(mysql.String(120), nullable=False)

    def __repr__(self):
        return '<Distributor (%s, %s) >' % (self.Name, self.WebSite)

# Location model
class Location(mysql.Model):  
    __tablename__ = 'location'
    Id = mysql.Column(mysql.Integer, primary_key=True)
    Position = mysql.Column(mysql.String(50), nullable=False)
    Container = mysql.Column(mysql.String(50), nullable=False)
    SubContainer = mysql.Column(mysql.String(50), nullable=False)

    def __repr__(self):
        return '<Location (%s, %s, %s) >' % (self.Position, self.Container, self.SubContainer)

# Footprint model
class Footprint(mysql.Model):  
    __tablename__ = 'footprint'
    Id = mysql.Column(mysql.Integer, primary_key=True)
    Name = mysql.Column(mysql.String(50), nullable=False)
    WebSite = mysql.Column(mysql.String(120), nullable=False)

    def __repr__(self):
        return '<Footprint (%s, %s) >' % (self.Name, self.WebSite)
#### END of Map Model ####

@api.route('/inventory/manufacturer', methods=['POST'])
<<<<<<< HEAD
@crossdomain(origin='*')
=======
>>>>>>> beta
def createManufacturer():
    name = request.get_json()["Name"]
    webSite = request.get_json()["WebSite"]

    manufacturer = Manufacturer(Name = name, WebSite = webSite)

    curr_session = mysql.session
    try:
        curr_session.add(manufacturer)
        curr_session.commit()
    except:
        curr_session.rollback()
        curr_session.flush()

    return jsonify(True)

@api.route('/inventory/manufacturer', methods=['GET'])
<<<<<<< HEAD
@crossdomain(origin='*')
=======
>>>>>>> beta
def getManufacturers():  
    data = Manufacturer.query.order_by(Manufacturer.Id.desc()).all()

    for manufacturer in data:
        mfields = { 'Id': fields.Raw, 'Name': fields.Raw, 'WebSite': fields.Raw }
        
    return jsonify(marshal(data, mfields))

@api.route('/inventory/manufacturer/<int:ID>', methods=['GET'])
<<<<<<< HEAD
@crossdomain(origin='*')
=======
>>>>>>> beta
def getManufacturer(ID):  
    data = Manufacturer.query.get(ID)
    mfields = { 'Id': fields.Raw, 'Name': fields.Raw, 'WebSite': fields.Raw }

    return jsonify(marshal(data, mfields))

<<<<<<< HEAD
@api.route('/inventory/manufacturer/<int:ID>', methods=['PUT', 'OPTIONS'])
@crossdomain(origin='*') 
=======
@api.route('/inventory/manufacturer/<int:ID>', methods=['PUT'])
>>>>>>> beta
def updateManufacturer(ID):
    name = request.get_json()["Name"]
    webSite = request.get_json()["WebSite"]
    curr_session = mysql.session

    try:
        manufacturer = Manufacturer.query.get(ID)
        manufacturer.Name = name
        manufacturer.WebSite = webSite
        curr_session.commit()
    except:
        curr_session.rollback()
        curr_session.flush()

    return jsonify(True)

<<<<<<< HEAD
@api.route('/inventory/manufacturer/<int:ID>', methods=['DELETE', 'OPTIONS'])
@crossdomain(origin='*')
=======
@api.route('/inventory/manufacturer/<int:ID>', methods=['DELETE'])
>>>>>>> beta
def deleteManufacturer(ID):
    curr_session = mysql.session

    curr_session.delete(Manufacturer.query.get(ID))
    curr_session.commit()

    return jsonify(True)

if __name__ == "__main__":  
    api.run(host = "192.168.1.37", port = "33")