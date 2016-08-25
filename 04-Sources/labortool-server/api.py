import ConfigParser
from datetime import timedelta
from flask_sqlalchemy import SQLAlchemy
from flask_restful import fields, marshal
from flask import Flask, jsonify, request, make_response, current_app
from functools import update_wrapper
from flask_cors import CORS, cross_origin

api = Flask(__name__)
CORS(api)


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

# Category model
class Category(mysql.Model):
    __tablename__ = 'category'
    Id = mysql.Column(mysql.Integer, primary_key=True)
    Name = mysql.Column(mysql.String(50), nullable=False)
    Note = mysql.Column(mysql.Text, nullable=False)

    def __repr__(self):
        return '<Footprint (%s, %s) >' % (self.Name, self.Note)

# CatParamType model
class CatParamType(mysql.Model):
    __tablename__ = 'catParamType'
    Id = mysql.Column(mysql.Integer, primary_key=True)
    Name = mysql.Column(mysql.String(50), nullable=False)
    CategoryId = mysql.Column(mysql.Integer, nullable=False)
    UnitId = mysql.Column(mysql.Integer, nullable=False)
    Order = mysql.Column(mysql.Integer, nullable=False)
    Note = mysql.Column(mysql.Text, nullable=False)

    def __repr__(self):
        return '<Footprint (%s, %s, %s) >' % (self.Name, self.Order, self.Note)

# Unit model
class Unit(mysql.Model):
    __tablename__ = 'unit'
    Id = mysql.Column(mysql.Integer, primary_key=True)
    Name = mysql.Column(mysql.String(50), nullable=False)
    ShortName = mysql.Column(mysql.String(50), nullable=False)
    Note = mysql.Column(mysql.Text, nullable=False)

    def __repr__(self):
        return '<Footprint (%s, %s, %s) >' % (self.Name, self.ShortName, self.Note)

# ComponentParam model
class ComponentParam(mysql.Model):
    __tablename__ = 'componentParam'
    Id = mysql.Column(mysql.Integer, primary_key=True)
    Name = mysql.Column(mysql.String(50), nullable=False)
    CategoryParamTypeId = mysql.Column(mysql.Integer, nullable=False)
    Value = mysql.Column(mysql.String(50), nullable=False)
    Prefix = mysql.Column(mysql.String(50), nullable=False)
    Note = mysql.Column(mysql.Text, nullable=False)

    def __repr__(self):
        return '<Footprint (%s, %s, %s, %s) >' % (self.Name, self.Value, self.Prefix, self.Note)

# Component model
class Component(mysql.Model):
    __tablename__ = 'component'
    Id = mysql.Column(mysql.Integer, primary_key=True)
    Name = mysql.Column(mysql.String(50), nullable=False)
    CategoryId = mysql.Column(mysql.Integer, nullable=False)
    PartNumber = mysql.Column(mysql.String(50), nullable=False)
    DistributorId = mysql.Column(mysql.Integer, nullable=False)
    DistributorCode = mysql.Column(mysql.String(50), nullable=False)
    Price = mysql.Column(mysql.String(50), nullable=False)
    Code = mysql.Column(mysql.String(50), nullable=False)
    LocationId = mysql.Column(mysql.Integer, nullable=False)
    CategoryId = mysql.Column(mysql.Integer, nullable=False)
    Note = mysql.Column(mysql.Text, nullable=False)

    def __repr__(self):
        return '<Footprint (%s, %s, %s, %s) >' % (self.Name, self.Value, self.Prefix, self.Note)

#### END of Map Model ####

#### Begin Manufacturer CRUD ####
@api.route('/inventory/manufacturer', methods=['POST'])
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
def getManufacturers():  
    data = Manufacturer.query.order_by(Manufacturer.Id.desc()).all()

    for manufacturer in data:
        mfields = { 'Id': fields.Raw, 'Name': fields.Raw, 'WebSite': fields.Raw }
        
    return jsonify(marshal(data, mfields))

@api.route('/inventory/manufacturer/<int:ID>', methods=['GET'])
def getManufacturer(ID):  
    data = Manufacturer.query.get(ID)
    mfields = { 'Id': fields.Raw, 'Name': fields.Raw, 'WebSite': fields.Raw }

    return jsonify(marshal(data, mfields))

@api.route('/inventory/manufacturer/<int:ID>', methods=['PUT'])
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

@api.route('/inventory/manufacturer/<int:ID>', methods=['DELETE'])
def deleteManufacturer(ID):
    curr_session = mysql.session

    curr_session.delete(Manufacturer.query.get(ID))
    curr_session.commit()

    return jsonify(True)
#### End Manufacturer CRUD ####

#### Begin Distributor CRUD ####
@api.route('/inventory/distributor', methods=['POST'])
def createDistributor():
    name = request.get_json()["Name"]
    webSite = request.get_json()["WebSite"]

    distributor = Distributor(Name = name, WebSite = webSite)

    curr_session = mysql.session
    try:
        curr_session.add(distributor)
        curr_session.commit()
    except:
        curr_session.rollback()
        curr_session.flush()

    return jsonify(True)

@api.route('/inventory/distributor', methods=['GET'])
def getDistributors():  
    data = Distributor.query.order_by(Distributor.Id.desc()).all()

    for distributor in data:
        mfields = { 'Id': fields.Raw, 'Name': fields.Raw, 'WebSite': fields.Raw }
        
    return jsonify(marshal(data, mfields))

@api.route('/inventory/distributor/<int:ID>', methods=['GET'])
def getDistributor(ID):  
    data = Distributor.query.get(ID)
    mfields = { 'Id': fields.Raw, 'Name': fields.Raw, 'WebSite': fields.Raw }

    return jsonify(marshal(data, mfields))

@api.route('/inventory/distributor/<int:ID>', methods=['PUT'])
def updateDistributor(ID):
    name = request.get_json()["Name"]
    webSite = request.get_json()["WebSite"]
    curr_session = mysql.session

    try:
        distributor = Distributor.query.get(ID)
        distributor.Name = name
        distributor.WebSite = webSite
        curr_session.commit()
    except:
        curr_session.rollback()
        curr_session.flush()

    return jsonify(True)

@api.route('/inventory/distributor/<int:ID>', methods=['DELETE'])
def deleteDistributor(ID):
    curr_session = mysql.session

    curr_session.delete(Distributor.query.get(ID))
    curr_session.commit()

    return jsonify(True)
#### End Distributor CRUD ####

#### Begin Location CRUD ####
@api.route('/inventory/location', methods=['POST'])
def createLocation():
    position = request.get_json()["Position"]
    container = request.get_json()["Container"]
    subContainer = request.get_json()["SubContainer"]

    location = Location(Position=position, Container=container, SubContainer=subContainer)

    curr_session = mysql.session
    try:
        curr_session.add(location)
        curr_session.commit()
    except:
        curr_session.rollback()
        curr_session.flush()

    return jsonify(True)

@api.route('/inventory/location', methods=['GET'])
def getLocations():  
    data = Location.query.order_by(Location.Id.desc()).all()

    for location in data:
        mfields = { 'Id': fields.Raw, 'Position': fields.Raw, 'Container': fields.Raw, 'SubContainer': fields.Raw }
        
    return jsonify(marshal(data, mfields))

@api.route('/inventory/location/<int:ID>', methods=['GET'])
def getLocation(ID):  
    data = Location.query.get(ID)
    mfields = { 'Id': fields.Raw, 'Position': fields.Raw, 'Container': fields.Raw, 'SubContainer': fields.Raw }

    return jsonify(marshal(data, mfields))

@api.route('/inventory/location/<int:ID>', methods=['PUT'])
def updateLocation(ID):
    position = request.get_json()["Position"]
    container = request.get_json()["Container"]
    subContainer = request.get_json()["SubContainer"]
    curr_session = mysql.session

    try:
        location = Location.query.get(ID)
        location.Position = position
        location.Container = container
        location.SubContainer = subContainer
        curr_session.commit()
    except:
        curr_session.rollback()
        curr_session.flush()

    return jsonify(True)

@api.route('/inventory/location/<int:ID>', methods=['DELETE'])
def deleteLocation(ID):
    curr_session = mysql.session

    curr_session.delete(Location.query.get(ID))
    curr_session.commit()

    return jsonify(True)
#### End Location CRUD ####

#### Begin Footprint CRUD ####
@api.route('/inventory/footprint', methods=['POST'])
def createFootprint():
    name = request.get_json()["Name"]
    webSite = request.get_json()["WebSite"]

    footprint = Footprint(Name = name, WebSite = webSite)

    curr_session = mysql.session
    try:
        curr_session.add(footprint)
        curr_session.commit()
    except:
        curr_session.rollback()
        curr_session.flush()

    return jsonify(True)

@api.route('/inventory/footprint', methods=['GET'])
def getFootprints():  
    data = Footprint.query.order_by(Footprint.Id.desc()).all()

    for footprint in data:
        mfields = { 'Id': fields.Raw, 'Name': fields.Raw, 'WebSite': fields.Raw }
        
    return jsonify(marshal(data, mfields))

@api.route('/inventory/footprint/<int:ID>', methods=['GET'])
def getFootprint(ID):  
    data = Footprint.query.get(ID)
    mfields = { 'Id': fields.Raw, 'Name': fields.Raw, 'WebSite': fields.Raw }

    return jsonify(marshal(data, mfields))

@api.route('/inventory/footprint/<int:ID>', methods=['PUT'])
def updateFootprint(ID):
    name = request.get_json()["Name"]
    webSite = request.get_json()["WebSite"]
    curr_session = mysql.session

    try:
        footprint = Footprint.query.get(ID)
        footprint.Name = name
        footprint.WebSite = webSite
        curr_session.commit()
    except:
        curr_session.rollback()
        curr_session.flush()

    return jsonify(True)

@api.route('/inventory/footprint/<int:ID>', methods=['DELETE'])
def deleteFootprint(ID):
    curr_session = mysql.session

    curr_session.delete(Footprint.query.get(ID))
    curr_session.commit()

    return jsonify(True)
#### End Footprint CRUD ####

#### Begin Category CRUD ####
@api.route('/inventory/category', methods=['POST'])
def createCategory():
    name = request.get_json()["Name"]
    note = request.get_json()["Note"]

    category = Category(Name = name, Note = note)

    curr_session = mysql.session
    try:
        curr_session.add(category)
        curr_session.commit()
    except:
        curr_session.rollback()
        curr_session.flush()

    return jsonify(True)

@api.route('/inventory/category', methods=['GET'])
def getCategorys():  
    data = Category.query.order_by(Category.Id.desc()).all()

    for category in data:
        mfields = { 'Id': fields.Raw, 'Name': fields.Raw, 'Note': fields.Raw }
        
    return jsonify(marshal(data, mfields))

@api.route('/inventory/category/<int:ID>', methods=['GET'])
def getCategory(ID):  
    data = Category.query.get(ID)
    mfields = { 'Id': fields.Raw, 'Name': fields.Raw, 'Note': fields.Raw }

    return jsonify(marshal(data, mfields))

@api.route('/inventory/category/<int:ID>', methods=['PUT'])
def updateCategory(ID):
    name = request.get_json()["Name"]
    note = request.get_json()["Note"]
    curr_session = mysql.session

    try:
        category = Category.query.get(ID)
        category.Name = name
        category.WebSite = note
        curr_session.commit()
    except:
        curr_session.rollback()
        curr_session.flush()

    return jsonify(True)

@api.route('/inventory/category/<int:ID>', methods=['DELETE'])
def deleteCategory(ID):
    curr_session = mysql.session

    curr_session.delete(Category.query.get(ID))
    curr_session.commit()

    return jsonify(True)
#### End Category CRUD ####

#### Begin CategoryParamType R ####
@api.route('/inventory/cat-param-type', methods=['GET'])
def getCatParamTypes():  
    data = CatParamType.query.order_by(CatParamType.Id.desc()).all()

    for catparamtype in data:
        mfields = { 'Id': fields.Raw, 'Name': fields.Raw, 'CategoryId': fields.Raw, 'UnitId': fields.Raw, 'Order': fields.Raw, 'Note': fields.Raw }
        
    return jsonify(marshal(data, mfields))

@api.route('/inventory/cat-param-type/<int:ID>', methods=['GET'])
def getCatParamType(ID):  
    data = CatParamType.query.get(ID)
    mfields = { 'Id': fields.Raw, 'Name': fields.Raw, 'CategoryId': fields.Raw, 'UnitId': fields.Raw, 'Order': fields.Raw, 'Note': fields.Raw }

    return jsonify(marshal(data, mfields))
#### End CategoryParamType R ####

#### Begin Unit R ####
@api.route('/inventory/unit', methods=['GET'])
def getUnits():  
    data = Unit.query.order_by(Unit.Id.desc()).all()

    for unit in data:
        mfields = { 'Id': fields.Raw, 'Name': fields.Raw, 'ShortName': fields.Raw, 'Note': fields.Raw }
        
    return jsonify(marshal(data, mfields))

@api.route('/inventory/unit/<int:ID>', methods=['GET'])
def getUnit(ID):  
    data = Unit.query.get(ID)
    mfields = { 'Id': fields.Raw, 'Name': fields.Raw, 'ShortName': fields.Raw, 'Note': fields.Raw }

    return jsonify(marshal(data, mfields))
#### End Unit R ####

#### Begin ComponentParam CRUD ####
@api.route('/inventory/component-param', methods=['POST'])
def createComponentParam():
    componentId = request.get_json()["ComponentId"]
    catParamTypeId = request.get_json()["CatParamTypeId"]
    value = request.get_json()["Value"]
    prefix = request.get_json()["Prefix"]
    note = request.get_json()["Note"]

    componentParam = Category(ComponentId=componentId, CatParamTypeId=catParamTypeId, Value=value, Prefix=prefix, Note=note)

    curr_session = mysql.session
    try:
        curr_session.add(componentParam)
        curr_session.commit()
    except:
        curr_session.rollback()
        curr_session.flush()

    return jsonify(True)

@api.route('/inventory/component-param', methods=['GET'])
def getComponentParams():  
    data = ComponentParam.query.order_by(ComponentParam.Id.desc()).all()

    for componentParam in data:
        mfields = { 'Id': fields.Raw, 'ComponentId': fields.Raw, 'CatParamTypeId': fields.Raw, 'Value': fields.Raw, 'Prefix': fields.Raw, 'Note': fields.Raw }
        
    return jsonify(marshal(data, mfields))

@api.route('/inventory/component-param/<int:ID>', methods=['GET'])
def getComponentParam(ID):  
    data = ComponentParam.query.get(ID)
    mfields = { 'Id': fields.Raw, 'ComponentId': fields.Raw, 'CatParamTypeId': fields.Raw, 'Value': fields.Raw, 'Prefix': fields.Raw, 'Note': fields.Raw }

    return jsonify(marshal(data, mfields))

@api.route('/inventory/component-param/<int:ID>', methods=['PUT'])
def updateComponentParam(ID):
    componentId = request.get_json()["ComponentId"]
    catParamTypeId = request.get_json()["CatParamTypeId"]
    value = request.get_json()["Value"]
    prefix = request.get_json()["Prefix"]
    note = request.get_json()["Note"]
    curr_session = mysql.session

    try:
        componentParam = ComponentParam.query.get(ID)
        componentParam.ComponentId = componentId
        componentParam.CatParamTypeId = catParamTypeId
        componentParam.Value = value
        componentParam.Prefix = prefix
        componentParam.Note = note
        curr_session.commit()
    except:
        curr_session.rollback()
        curr_session.flush()

    return jsonify(True)

@api.route('/inventory/component-param/<int:ID>', methods=['DELETE'])
def deleteComponentParam(ID):
    curr_session = mysql.session

    curr_session.delete(ComponentParam.query.get(ID))
    curr_session.commit()

    return jsonify(True)
#### End Category CRUD ####

#### Begin Category CRUD ####
@api.route('/inventory/component', methods=['POST'])
def createComponent():
    name = request.get_json()["Name"]
    manufacturerId = request.get_json()["ManufacturerId"]
    partNamber = request.get_json()["PartNamber"]
    distributorId = request.get_json()["DistributorId"]
    distributorCode = request.get_json()["DistributorCode"]
    price = request.get_json()["Price"]
    locationId = request.get_json()["LocationId"]
    datasheet = request.get_json()["Datasheet"]
    footprintId = request.get_json()["FootprintId"]
    categoryId = request.get_json()["CategoryId"]
    note = request.get_json()["Note"]

    component = Component(Name=name, ManufacturerId=manufacturerId, PartNamber=partNamber, DistributorId=distributorId, DistributorCode=distributorCode, Price=price, LocationId=locationId, Datasheet=datasheet, FootprintId=footprintId, CategoryId=categoryId, Note=note)

    curr_session = mysql.session
    try:
        curr_session.add(component)
        curr_session.commit()
    except:
        curr_session.rollback()
        curr_session.flush()

    return jsonify(True)

@api.route('/inventory/component', methods=['GET'])
def getComponents():  
    data = Component.query.order_by(Component.Id.desc()).all()

    for component in data:
        mfields = { 'Id': fields.Raw, 'Name': fields.Raw, 'ManufacturerId': fields.Raw, 'PartNumber': fields.Raw, \
                    'DistributorId': fields.Raw, 'DistributorCode': fields.Raw, 'Price': fields.Raw, 'Code': fields.Raw, \
                    'LocationId': fields.Raw, 'Datasheet': fields.Raw, 'FootprintId': fields.Raw, 'CategoryId': fields.Raw, \
                    'Note': fields.Raw }
        
    return jsonify(marshal(data, mfields))

@api.route('/inventory/component/<int:ID>', methods=['GET'])
def getComponent(ID):  
    data = Component.query.get(ID)
    mfields = { 'Id': fields.Raw, 'Name': fields.Raw, 'ManufacturerId': fields.Raw, 'PartNumber': fields.Raw, \
                'DistributorId': fields.Raw, 'DistributorCode': fields.Raw, 'Price': fields.Raw, 'Code': fields.Raw, \
                'LocationId': fields.Raw, 'Datasheet': fields.Raw, 'FootprintId': fields.Raw, 'CategoryId': fields.Raw, \
                'Note': fields.Raw }

    return jsonify(marshal(data, mfields))

@api.route('/inventory/component/<int:ID>', methods=['PUT'])
def updateComponent(ID):
    name = request.get_json()["Name"]
    manufacturerId = request.get_json()["ManufacturerId"]
    partNamber = request.get_json()["PartNamber"]
    distributorId = request.get_json()["DistributorId"]
    distributorCode = request.get_json()["DistributorCode"]
    price = request.get_json()["Price"]
    locationId = request.get_json()["LocationId"]
    datasheet = request.get_json()["Datasheet"]
    footprintId = request.get_json()["FootprintId"]
    categoryId = request.get_json()["CategoryId"]
    note = request.get_json()["Note"]
    curr_session = mysql.session

    try:
        component = Component.query.get(ID)
        component.Name = name
        component.ManufacturerId = manufacturerId
        component.PartNumber = partNumber 
        component.DistributorId = distributorId 
        component.DistributorCode = distributorCode 
        component.Price = price 
        component.LocationId = locationId 
        component.Datasheet = datasheet 
        component.FootprintId = footprintId 
        component.CategoryId = categoryId 
        component.Note = note 
        curr_session.commit()
    except:
        curr_session.rollback()
        curr_session.flush()

    return jsonify(True)

@api.route('/inventory/component/<int:ID>', methods=['DELETE'])
def deleteComponent(ID):
    curr_session = mysql.session

    curr_session.delete(Component.query.get(ID))
    curr_session.commit()

    return jsonify(True)
#### End Category CRUD ####

if __name__ == "__main__":  
    api.run(host = "172.17.82.53", port = "33")