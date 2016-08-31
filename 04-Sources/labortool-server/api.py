import ConfigParser
from datetime import timedelta
from flask_sqlalchemy import SQLAlchemy
from flask_restful import fields, marshal
from flask import Flask, jsonify, request, make_response, current_app
from functools import update_wrapper
from flask_cors import CORS, cross_origin
from sqlalchemy import Table, Column, Integer, ForeignKey, Float, Enum
from sqlalchemy.orm import relationship

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
    ManufacturerId = mysql.Column(mysql.Integer, primary_key=True, nullable=False)
    ManufacturerName = mysql.Column(mysql.String(45), nullable=False)
    ManufacturerWebSite = mysql.Column(mysql.String(45), nullable=False)

# Distributor model
class Distributor(mysql.Model):  
    __tablename__ = 'distributor'
    DistributorId = mysql.Column(mysql.Integer, primary_key=True, nullable=False)
    DistributorName = mysql.Column(mysql.String(45), nullable=False)
    DistributorWebSite = mysql.Column(mysql.String(45), nullable=False)

# Location model
class Location(mysql.Model):  
    __tablename__ = 'location'
    LocationId = mysql.Column(mysql.Integer, primary_key=True, nullable=False)
    LocationPosition = mysql.Column(mysql.String(45), nullable=False)
    LocationContainer = mysql.Column(mysql.String(45), nullable=False)
    LocationSubContainer = mysql.Column(mysql.String(45), nullable=False)

# Footprint model
class Footprint(mysql.Model):  
    __tablename__ = 'footprint'
    FootprintId = mysql.Column(mysql.Integer, primary_key=True, nullable=False)
    FootprintName = mysql.Column(mysql.String(45), nullable=False)
    FootprintLink = mysql.Column(mysql.String(200), nullable=False)

# Category model
class Category(mysql.Model):
    __tablename__ = 'category'
    CategoryId = mysql.Column(mysql.Integer, primary_key=True, nullable=False)
    CategoryName = mysql.Column(mysql.String(45), nullable=False)
    CategoryNote = mysql.Column(mysql.String(45), nullable=True)

# CategoryParamType model
class CategoryParamType(mysql.Model):
    __tablename__ = 'category-param-type'
    CategoryParamTypeId = mysql.Column(mysql.Integer, primary_key=True, nullable=False)
    CategoryParamTypeName = mysql.Column(mysql.String(45), nullable=False)
    CategoryParamTypeCategory = mysql.Column(mysql.Integer, mysql.ForeignKey('category.CategoryId'), nullable=False)
    CategoryParamTypeUnit = mysql.Column(mysql.Integer, mysql.ForeignKey('unit.UnitId'), nullable=False)
    CategoryParamTypeOrder = mysql.Column(mysql.String(45), nullable=False)
    CategoryParamTypeNote = mysql.Column(mysql.String(45), nullable=True)

# Unit model
class Unit(mysql.Model):
    __tablename__ = 'unit'
    UnitId = mysql.Column(mysql.Integer, primary_key=True, nullable=False)
    UnitName = mysql.Column(mysql.String(45), nullable=False)
    UnitShortName = mysql.Column(mysql.String(5), nullable=False)
    UnitNote = mysql.Column(mysql.String(45), nullable=True)

# ComponentParam model
class ComponentParam(mysql.Model):
    __tablename__ = 'component-param'
    ComponentParamId = mysql.Column(mysql.Integer, primary_key=True, nullable=False)
    ComponentParamComponent = mysql.Column(mysql.Integer, mysql.ForeignKey('component.ComponentId'), nullable=False)
    ComponentParamCategoryParamType = mysql.Column(mysql.Integer, mysql.ForeignKey('categoryparamtype.CategoryParamTypeId'), nullable=False)
    ComponentParamValue = mysql.Column(mysql.String(45), nullable=False)
    ComponentParamPrefix = mysql.Column(mysql.Enum("femto", "pico", "nano", "micro", "milli", "unit", "kilo", "mega", "giga", "tera"), nullable=False)
    ComponentParamNote = mysql.Column(mysql.String(45), nullable=False)

# Component model
class Component(mysql.Model):
    __tablename__ = 'component'
    ComponentId = mysql.Column(mysql.Integer, primary_key=True, nullable=False)
    ComponentName = mysql.Column(mysql.String(45), nullable=False)
    ComponentManufacturer = mysql.Column(mysql.Integer, mysql.ForeignKey('manufacturer.ManufacturerId'), nullable=False)
    _manufacturer = relationship("Manufacturer", foreign_keys = "[Component.ComponentManufacturer]")
    ComponentPartNumber = mysql.Column(mysql.String(45), nullable=False)
    ComponentDistributor = mysql.Column(mysql.Integer, mysql.ForeignKey('distributor.DistributorId'), nullable=False)
    ComponentDistributorCode = mysql.Column(mysql.String(45), nullable=False)
    ComponentPrice = mysql.Column(mysql.Float, nullable=False)
    ComponentCode = mysql.Column(mysql.String(45), nullable=False)
    ComponentLocation = mysql.Column(mysql.Integer, mysql.ForeignKey('location.DistributorId'), nullable=False)
    ComponentDatasheet = mysql.Column(mysql.String(45), nullable=False)
    ComponentFootprint = mysql.Column(mysql.Integer, mysql.ForeignKey('footprint.FoorprintId'), nullable=False)
    ComponentCategory = mysql.Column(mysql.Integer, mysql.ForeignKey('category.CategoryId'), nullable=False)
    ComponentNote = mysql.Column(mysql.String(45), nullable=True)

#### END of Map Model ####

#### Begin Manufacturer CRUD ####
@api.route('/inventory/manufacturer', methods=['POST'])
def createManufacturer():
    name = request.get_json()["ManufacturerName"]
    webSite = request.get_json()["ManufacturerWebSite"]

    manufacturer = Manufacturer(ManufacturerName = name, ManufacturerWebSite = webSite)

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
    data = Manufacturer.query.order_by(Manufacturer.ManufacturerId.desc()).all()

    for manufacturer in data:
        mfields = { 'ManufacturerId': fields.Raw, 'ManufacturerName': fields.Raw, 'ManufacturerWebSite': fields.Raw }
        
    return jsonify(marshal(data, mfields))

@api.route('/inventory/manufacturer/<int:ID>', methods=['GET'])
def getManufacturer(ID):  
    data = Manufacturer.query.get(ID)
    mfields = { 'ManufacturerId': fields.Raw, 'ManufacturerName': fields.Raw, 'ManufacturerWebSite': fields.Raw }

    return jsonify(marshal(data, mfields))

@api.route('/inventory/manufacturer/<int:ID>', methods=['PUT'])
def updateManufacturer(ID):
    name = request.get_json()["ManufacturerName"]
    webSite = request.get_json()["ManufacturerWebSite"]
    curr_session = mysql.session

    try:
        manufacturer = Manufacturer.query.get(ID)
        manufacturer.ManufacturerName = name
        manufacturer.ManufacturerWebSite = webSite
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
    name = request.get_json()["DistributorName"]
    webSite = request.get_json()["DistributorWebSite"]

    distributor = Distributor(DistributorName = name, DistributorWebSite = webSite)

    curr_session = mysql.session
    try:
        curr_session.add(distributor)
        curr_session.commit()
    except:
        curr_session.rollback()
        curr_session.flush()

    return jsonify(True)

@api.route('/inventory/distributor', methods = ['GET'])
def getDistributors():  
    data = Distributor.query.order_by(Distributor.DistributorId.desc()).all()

    for distributor in data:
        mfields = { 'DistributorId': fields.Raw, 'DistributorName': fields.Raw, 'DistributorWebSite': fields.Raw }
        
    return jsonify(marshal(data, mfields))

@api.route('/inventory/distributor/<int:ID>', methods = ['GET'])
def getDistributor(ID):  
    data = Distributor.query.get(ID)
    mfields = { 'DistributorId': fields.Raw, 'DistributorName': fields.Raw, 'DistributorWebSite': fields.Raw }

    return jsonify(marshal(data, mfields))

@api.route('/inventory/distributor/<int:ID>', methods = ['PUT'])
def updateDistributor(ID):
    name = request.get_json()["DistributorName"]
    webSite = request.get_json()["DistributorWebSite"]
    curr_session = mysql.session

    try:
        distributor = Distributor.query.get(ID)
        distributor.DistributorName = name
        distributor.DistributorWebSite = webSite
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
@api.route('/inventory/location', methods = ['POST'])
def createLocation():
    position = request.get_json()["LocationPosition"]
    container = request.get_json()["LocationContainer"]
    subContainer = request.get_json()["LocationSubContainer"]

    location = Location(LocationPosition = position, LocationContainer = container, LocationSubContainer = subContainer)

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
    data = Location.query.order_by(Location.LocationId.desc()).all()

    for location in data:
        mfields = { 'LocationId': fields.Raw, 'LocationPosition': fields.Raw, 'LocationContainer': fields.Raw, 'LocationSubContainer': fields.Raw }
        
    return jsonify(marshal(data, mfields))

@api.route('/inventory/location/<int:ID>', methods = ['GET'])
def getLocation(ID):  
    data = Location.query.get(ID)
    mfields = { 'LocationId': fields.Raw, 'LocationPosition': fields.Raw, 'LocationContainer': fields.Raw, 'LocationSubContainer': fields.Raw }

    return jsonify(marshal(data, mfields))

@api.route('/inventory/location/<int:ID>', methods = ['PUT'])
def updateLocation(ID):
    position = request.get_json()["LocationPosition"]
    container = request.get_json()["LocationContainer"]
    subContainer = request.get_json()["LocationSubContainer"]
    curr_session = mysql.session

    try:
        location = Location.query.get(ID)
        location.LocationPosition = position
        location.LocationContainer = container
        location.LocationSubContainer = subContainer
        curr_session.commit()
    except:
        curr_session.rollback()
        curr_session.flush()

    return jsonify(True)

@api.route('/inventory/location/<int:ID>', methods = ['DELETE'])
def deleteLocation(ID):
    curr_session = mysql.session

    curr_session.delete(Location.query.get(ID))
    curr_session.commit()

    return jsonify(True)
#### End Location CRUD ####

#### Begin Footprint CRUD ####
@api.route('/inventory/footprint', methods = ['POST'])
def createFootprint():
    name = request.get_json()["FootprintName"]
    link = request.get_json()["FootprintLink"]

    footprint = Footprint(FootprintName = name, FootprintLink = link)

    curr_session = mysql.session
    try:
        curr_session.add(footprint)
        curr_session.commit()
    except:
        curr_session.rollback()
        curr_session.flush()

    return jsonify(True)

@api.route('/inventory/footprint', methods = ['GET'])
def getFootprints():  
    data = Footprint.query.order_by(Footprint.FootprintId.desc()).all()

    for footprint in data:
        mfields = { 'FootprintId': fields.Raw, 'FootprintName': fields.Raw, 'FootprintLink': fields.Raw }
        
    return jsonify(marshal(data, mfields))

@api.route('/inventory/footprint/<int:ID>', methods = ['GET'])
def getFootprint(ID):  
    data = Footprint.query.get(ID)
    mfields = { 'FootprintId': fields.Raw, 'FootprintName': fields.Raw, 'FootprintLink': fields.Raw }

    return jsonify(marshal(data, mfields))

@api.route('/inventory/footprint/<int:ID>', methods=['PUT'])
def updateFootprint(ID):
    name = request.get_json()["FootprintName"]
    Link = request.get_json()["FootprintLink"]
    curr_session = mysql.session

    try:
        footprint = Footprint.query.get(ID)
        footprint.FootprintName = name
        footprint.FootprintLink = link
        curr_session.commit()
    except:
        curr_session.rollback()
        curr_session.flush()

    return jsonify(True)

@api.route('/inventory/footprint/<int:ID>', methods = ['DELETE'])
def deleteFootprint(ID):
    curr_session = mysql.session

    curr_session.delete(Footprint.query.get(ID))
    curr_session.commit()

    return jsonify(True)
#### End Footprint CRUD ####

#### Begin Category CRUD ####
@api.route('/inventory/category', methods = ['POST'])
def createCategory():
    name = request.get_json()["CategoryName"]
    note = request.get_json()["CategoryNote"]

    category = Category(CategoryName = name, CategoryNote = note)

    curr_session = mysql.session
    try:
        curr_session.add(category)
        curr_session.commit()
    except:
        curr_session.rollback()
        curr_session.flush()

    return jsonify(True)

@api.route('/inventory/category', methods = ['GET'])
def getCategorys():  
    data = Category.query.order_by(Category.CategoryId.desc()).all()

    for category in data:
        mfields = { 'CategoryId': fields.Raw, 'CategoryName': fields.Raw, 'CategoryNote': fields.Raw }
        
    return jsonify(marshal(data, mfields))

@api.route('/inventory/category/<int:ID>', methods = ['GET'])
def getCategory(ID):  
    data = Category.query.get(ID)
    mfields = { 'CategoryId': fields.Raw, 'CategoryName': fields.Raw, 'CategoryNote': fields.Raw }

    return jsonify(marshal(data, mfields))

@api.route('/inventory/category/<int:ID>', methods = ['PUT'])
def updateCategory(ID):
    name = request.get_json()["CategoryName"]
    note = request.get_json()["CategoryNote"]
    curr_session = mysql.session

    try:
        category = Category.query.get(ID)
        category.CategoryName = name
        category.CategoryWebSite = note
        curr_session.commit()
    except:
        curr_session.rollback()
        curr_session.flush()

    return jsonify(True)

@api.route('/inventory/category/<int:ID>', methods = ['DELETE'])
def deleteCategory(ID):
    curr_session = mysql.session

    curr_session.delete(Category.query.get(ID))
    curr_session.commit()

    return jsonify(True)
#### End Category CRUD ####

#### Begin CategoryParamType R ####
@api.route('/inventory/cat-param-type', methods=['GET'])
def getCatParamTypes():  
    data = CategoryParamType.query.order_by(CategoryParamType.CategoryParamTypeId.desc()).all()

    for catparamtype in data:
        mfields = { 'CategoryParamTypeId': fields.Raw, 'CategoryParamTypeName': fields.Raw, 'CategoryParamTypeCategory': fields.Raw, \
                    'CategoryParamTypeUnit': fields.Raw, 'CategoryParamTypeOrder': fields.Raw, 'CategoryParamTypeNote': fields.Raw }
        
    return jsonify(marshal(data, mfields))

@api.route('/inventory/cat-param-type/<int:ID>', methods = ['GET'])
def getCatParamType(ID):  
    data = CatParamType.query.get(ID)
    mfields = { 'CategoryParamTypeId': fields.Raw, 'CategoryParamTypeName': fields.Raw, 'CategoryParamTypeCategory': fields.Raw, \
                'CategoryParamTypeUnit': fields.Raw, 'CategoryParamTypeOrder': fields.Raw, 'CategoryParamTypeNote': fields.Raw }

    return jsonify(marshal(data, mfields))
#### End CategoryParamType R ####

#### Begin Unit R ####
@api.route('/inventory/unit', methods = ['GET'])
def getUnits():  
    data = Unit.query.order_by(Unit.UnitId.desc()).all()

    for unit in data:
        mfields = { 'UnitId': fields.Raw, 'UnitName': fields.Raw, 'UnitShortName': fields.Raw, 'UnitNote': fields.Raw }
        
    return jsonify(marshal(data, mfields))

@api.route('/inventory/unit/<int:ID>', methods = ['GET'])
def getUnit(ID):  
    data = Unit.query.get(ID)
    mfields = { 'UnitId': fields.Raw, 'UnitName': fields.Raw, 'UnitShortName': fields.Raw, 'UnitNote': fields.Raw }

    return jsonify(marshal(data, mfields))
#### End Unit R ####

#### Begin ComponentParam CRUD ####
@api.route('/inventory/component-param', methods = ['POST'])
def createComponentParam():
    componentId = request.get_json()["ComponentParamComponent"]
    catParamTypeId = request.get_json()["ComponentParamCategoryParamType"]
    value = request.get_json()["ComponentParamValue"]
    prefix = request.get_json()["ComponentParamPrefix"]
    note = request.get_json()["ComponentParamNote"]

    componentParam = ComponentParam(ComponentParam = componentId, ComponentParamCategoryParamType = catParamTypeId, \
                                    ComponentParamValue = value, ComponentParamPrefix = prefix, ComponentParamNote = note)

    curr_session = mysql.session
    try:
        curr_session.add(componentParam)
        curr_session.commit()
    except:
        curr_session.rollback()
        curr_session.flush()

    return jsonify(True)

@api.route('/inventory/component-param', methods = ['GET'])
def getComponentParams():  
    data = ComponentParam.query.order_by(ComponentParam.ComponentParamId.desc()).all()

    for componentParam in data:
        mfields = { 'ComponentParamId': fields.Raw, 'ComponentParamComponent': fields.Raw, 'ComponentParamCategoryParamType': fields.Raw, \
                    'ComponentParamValue': fields.Raw, 'ComponentParamPrefix': fields.Raw, 'ComponentParamNote': fields.Raw }
        
    return jsonify(marshal(data, mfields))

@api.route('/inventory/component-param/<int:ID>', methods = ['GET'])
def getComponentParam(ID):  
    data = ComponentParam.query.get(ID)
    mfields = { 'ComponentParamId': fields.Raw, 'ComponentParamComponent': fields.Raw, 'ComponentParamCategoryParamType': fields.Raw, \
                'ComponentParamValue': fields.Raw, 'ComponentParamPrefix': fields.Raw, 'ComponentParamNote': fields.Raw }

    return jsonify(marshal(data, mfields))

@api.route('/inventory/component-param/<int:ID>', methods = ['PUT'])
def updateComponentParam(ID):
    componentId = request.get_json()["ComponentParamComponent"]
    catParamTypeId = request.get_json()["ComponentParamCategoryParamType"]
    value = request.get_json()["ComponentParamValue"]
    prefix = request.get_json()["ComponentParamPrefix"]
    note = request.get_json()["ComponentParamNote"]
    
    curr_session = mysql.session
    try:
        componentParam = ComponentParam.query.get(ID)
        componentParam.ComponentParamComponent = componentId
        componentParam.ComponentParamCategoryParamType = catParamTypeId
        componentParam.ComponentParamValue = value
        componentParam.ComponentParamPrefix = prefix
        componentParam.ComponentParamNote = note
        curr_session.commit()
    except:
        curr_session.rollback()
        curr_session.flush()

    return jsonify(True)

@api.route('/inventory/component-param/<int:ID>', methods = ['DELETE'])
def deleteComponentParam(ID):
    curr_session = mysql.session

    curr_session.delete(ComponentParam.query.get(ID))
    curr_session.commit()

    return jsonify(True)
#### End Category CRUD ####

#### Begin Category CRUD ####
@api.route('/inventory/component', methods = ['POST'])
def createComponent():
    name = request.get_json()["ComponentName"]
    manufacturerId = request.get_json()["ComponentManufacturer"]
    partNamber = request.get_json()["ComponentPartNamber"]
    distributorId = request.get_json()["ComponentDistributor"]
    distributorCode = request.get_json()["ComponentDistributorCode"]
    price = request.get_json()["ComponentPrice"]
    locationId = request.get_json()["ComponentLocation"]
    datasheet = request.get_json()["ComponentDatasheet"]
    footprintId = request.get_json()["ComponentFootprint"]
    categoryId = request.get_json()["ComponentCategory"]
    note = request.get_json()["ComponentNote"]

    component = Component(ComponentName = name, ComponentManufacturer = manufacturerId, ComponentPartNamber = partNamber, \
                          ComponentDistributor = distributorId, ComponentDistributorCode = distributorCode, ComponentPrice = price, \
                          ComponentLocation = locationId, ComponentDatasheet = datasheet, ComponentFootprint = footprintId, \
                          ComponentCategory = categoryId, ComponentNote = note)

    curr_session = mysql.session
    try:
        curr_session.add(component)
        curr_session.commit()
    except:
        curr_session.rollback()
        curr_session.flush()

    return jsonify(True)

@api.route('/inventory/component', methods = ['GET'])
def getComponents():  
    #data = Component.query.join(Manufacturer).all()
    data = Component.query.order_by(Component.ComponentId.desc()).all()

    for component in data:
       mfields = { 'ComponentId': fields.Raw, 'ComponentName': fields.Raw, 'ComponentManufacturer': fields.Raw, 'ComponentPartNumber': fields.Raw, \
                   'ComponentDistributor': fields.Raw, 'ComponentDistributorCode': fields.Raw, 'ComponentPrice': fields.Raw, 'ComponentCode': fields.Raw, \
                   'ComponentLocation': fields.Raw, 'ComponentDatasheet': fields.Raw, 'ComponentFootprint': fields.Raw, 'ComponentCategory': fields.Raw, \
                   'ComponentNote': fields.Raw }
        
    return jsonify(marshal(data, mfields))

@api.route('/inventory/component/<int:ID>', methods = ['GET'])
def getComponent(ID):  
    data = Component.query.get(ID)
    mfields = { 'ComponentId': fields.Raw, 'ComponentName': fields.Raw, 'ComponentManufacturer': fields.Raw, 'ComponentPartNumber': fields.Raw, \
                'ComponentDistributor': fields.Raw, 'ComponentDistributorCode': fields.Raw, 'ComponentPrice': fields.Raw, 'ComponentCode': fields.Raw, \
                'ComponentLocation': fields.Raw, 'ComponentDatasheet': fields.Raw, 'ComponentFootprint': fields.Raw, 'ComponentCategory': fields.Raw, \
                'ComponentNote': fields.Raw }

    return jsonify(marshal(data, mfields))

@api.route('/inventory/component/<int:ID>', methods = ['PUT'])
def updateComponent(ID):
    name = request.get_json()["ComponentName"]
    manufacturerId = request.get_json()["ComponentManufacturer"]
    partNamber = request.get_json()["ComponentPartNamber"]
    distributorId = request.get_json()["ComponentDistributor"]
    distributorCode = request.get_json()["ComponentDistributorCode"]
    price = request.get_json()["ComponentPrice"]
    locationId = request.get_json()["ComponentLocation"]
    datasheet = request.get_json()["ComponentDatasheet"]
    footprintId = request.get_json()["ComponentFootprint"]
    categoryId = request.get_json()["ComponentCategory"]
    note = request.get_json()["ComponentNote"]

    curr_session = mysql.session
    try:
        component = Component.query.get(ID)
        component.ComponentName = name
        component.ComponentManufacturer = manufacturerId
        component.ComponentPartNumber = partNumber 
        component.ComponentDistributor = distributorId 
        component.ComponentDistributorCode = distributorCode 
        component.ComponentPrice = price 
        component.ComponentLocation = locationId 
        component.ComponentDatasheet = datasheet 
        component.ComponentFootprint = footprintId 
        component.ComponentCategory = categoryId 
        component.ComponentNote = note 
        curr_session.commit()
    except:
        curr_session.rollback()
        curr_session.flush()

    return jsonify(True)

@api.route('/inventory/component/<int:ID>', methods = ['DELETE'])
def deleteComponent(ID):
    curr_session = mysql.session

    curr_session.delete(Component.query.get(ID))
    curr_session.commit()

    return jsonify(True)
#### End Category CRUD ####

if __name__ == "__main__":  
    api.run(host = "192.168.1.37", port = "33")