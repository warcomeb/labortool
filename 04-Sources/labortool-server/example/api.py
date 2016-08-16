import ConfigParser  
from flask_sqlalchemy import SQLAlchemy  
from flask import Flask, jsonify, request

application = Flask(__name__)

# Read config file
config = ConfigParser.ConfigParser()  
config.read('rating_db.conf')

# MySQL configurations
application.config['SQLALCHEMY_DATABASE_URI'] = 'mysql+mysqldb://' + config.get('DB', 'user') + ':' + config.get('DB', 'password') + '@' + config.get('DB', 'host') + '/' + config.get('DB', 'db')

application.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = True

mysql = SQLAlchemy()
mysql.init_app(application)

# map models
class Products(mysql.Model):  
    __tablename__ = 'products'
    id = mysql.Column(mysql.Integer, primary_key=True)
    rate = mysql.Column(mysql.Integer, nullable=False)
    name = mysql.Column(mysql.String(128), nullable=False)

    def __repr__(self):
        return '<Products (%s, %s) >' % (self.rate, self.name)

@application.route("/")
def hello():  
    return "Hello World!"

@application.route('/product', methods=['POST'])
def createProduct():

    # fetch name and rate from the request
    rate = request.get_json()["rate"]
    name = request.get_json()["name"]

    product = Products(rate=rate, name=name) #prepare query statement

    curr_session = mysql.session #open database session
    try:
        curr_session.add(product) #add prepared statment to opened session
        curr_session.commit() #commit changes
    except:
        curr_session.rollback()
        curr_session.flush() # for resetting non-commited .add()

    data = Products.query.order_by(Products.id.desc()).first() #fetch our inserted product

    config.read('rating_db.conf')

    result = [data.id, data.rate, data.name] #prepare visual data

    return jsonify(session=result)

@application.route('/product', methods=['GET'])
def getProduct():  
    data = Products.query.all() #fetch all products on the table

    data_all = []

    for product in data:
        data_all.append([product.id, product.name, product.rate]) #prepare visual data

    return jsonify(products=data_all)

@application.route('/<int:productId>/product', methods=['PATCH']) 
def updateProduct(productId):

    rate = request.get_json()["rate"] #fetch rate
    curr_session = mysql.session

    try:
        product = Products.query.filter_by(id=productId).first() #fetch the product do be updated
        product.rate = rate #update the column rate with the info fetched from the request
        curr_session.commit() #commit changes
    except:
        curr_session.rollback()
        curr_session.flush()

    productId = product.id
    data = Products.query.filter_by(id=productId).first() #fetch our updated product

    config.read('rating_db.conf')

    result = [data.name, data.rate] #prepare visual data

    return jsonify(session=result)

@application.route('/product/<int:productId>', methods=['DELETE'])
def deleteProduct(productId):

    curr_session = mysql.session #initiate database session

    Products.query.filter_by(id=productId).delete() #find the product by productId and deletes it
    curr_session.commit() #commit changes to the database

    return getProduct() #return all create products

if __name__ == "__main__":  
    application.run()