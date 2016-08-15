#from api import mysql
from __init__ import mysql

##### Map models #####

# Manufacturer model
class Manufacturer(mysql.Model):  
    __tablename__ = 'manufacturer'
    Id = mysql.Column(mysql.Integer, primary_key=True)
    Name = mysql.Column(mysql.String(50), nullable=False)
    WebSite = mysql.Column(mysql.String(120), nullable=False)

    def __repr__(self):
        return '<Products (%s, %s) >' % (self.Name, self.WebSite)

# Distributor model
class Distributor(mysql.Model):  
    __tablename__ = 'distributor'
    Id = mysql.Column(mysql.Integer, primary_key=True)
    Name = mysql.Column(mysql.String(50), nullable=False)
    WebSite = mysql.Column(mysql.String(120), nullable=False)

    def __repr__(self):
        return '<Products (%s, %s) >' % (self.Name, self.WebSite)

# Location model
class Location(mysql.Model):  
    __tablename__ = 'location'
    Id = mysql.Column(mysql.Integer, primary_key=True)
    Position = mysql.Column(mysql.String(50), nullable=False)
    Container = mysql.Column(mysql.String(50), nullable=False)
    SubContainer = mysql.Column(mysql.String(50), nullable=False)

    def __repr__(self):
        return '<Products (%s, %s, %s) >' % (self.Position, self.Container, self.SubContainer)

# Footprint model
class Footprint(mysql.Model):  
    __tablename__ = 'footprint'
    Id = mysql.Column(mysql.Integer, primary_key=True)
    Name = mysql.Column(mysql.String(50), nullable=False)
    WebSite = mysql.Column(mysql.String(120), nullable=False)

    def __repr__(self):
        return '<Products (%s, %s) >' % (self.Name, self.WebSite)