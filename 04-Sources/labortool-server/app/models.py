from app import db

class User(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    nickname = db.Column(db.String(64), index=True, unique=True)
    password = db.Column(db.String(64), index=True, unique=False)
    email = db.Column(db.String(120), index=True, unique=True)

    def __repr__(self):                                                 #how the class will be printed
        return '<User %r>' % (self.nickname)

class Component(db.Model):
    Id = db.Column(db.Integer, primary_key=True)
    Name = db.Column(db.String(64), index=True, unique=False)
    ManufacturerId = db.Column(db.Integer, db.ForeignKey('manufacturer.Id'))
    PartNumber = db.Column(db.String(64), index=True, unique=False)
    DistributorId = db.Column(db.Integer, db.ForeignKey('distributor.Id'))
    DistributorCode = db.Column(db.String(64), index=True, unique=False)
    Price = db.Column(db.Float, index=True, unique=False)
    Code = db.Column(db.String(64), index=True, unique=True)
    LocationId = db.Column(db.Integer, db.ForeignKey('location.Id'))
    CategoryId = db.Column(db.Integer, db.ForeignKey('category.Id'))
    LinkDatasheet = db.Column(db.String(64), index=True, unique=True)
    Note = db.Column(db.String(64), index=True, unique=False)

    def __repr__(self):
        return '<Component %r>' % (self.Name)

class Manufacturer(db.Model):
    Id = db.Column(db.Integer, primary_key=True)
    Name = db.Column(db.String(64), index=True, unique=False)
    WebSite = db.Column(db.String(120), index=True, unique=True)

    def __repr_(self):
        return '<Manufacturer %r>' % (self.WebSite)

class Distributor(db.Model):
    Id = db.Column(db.Integer, primary_key=True)
    Name = db.Column(db.String(64), index=True, unique=False)
    WebSite = db.Column(db.String(120), index=True, unique=True)
    
    def __repr__(self):
        return '<Distributor %r>' % (self.WebSite)

class Location(db.Model):
    Id = db.Column(db.Integer, primary_key=True)
    Position = db.Column(db.String(64), index=True, unique=False)
    Container = db.Column(db.String(64), index=True, unique=False)

    def __repr__(self):
        return '<Location %r>' % (self.Position, self.Container)

class Category(db.Model):
    Id = db.Column(db.Integer, primary_key=True)
    Name = db.Column(db.String(64), index=True, unique=False)
    Note = db.Column(db.String(120), index=True, unique=False)

    def __repr__(self):
        return '<Category %r>' % (self.Name, self.Note)

class CategoryParamType(db.Model):
    Id = db.Column(db.Integer, primary_key=True)
    Name = db.Column(db.String(64), index=True, unique=False)
    CategoryId = db.Column(db.Integer, db.ForeignKey('category.Id'))
    LimitUp = db.Column(db.String(64), index=True, unique=False)
    UnitId = db.Column(db.Integer, db.ForeignKey('unit.Id'))
    Type = db.Column(db.String(64), index=True, unique=False)
    Note = db.Column(db.String(64), index=True, unique=False)

    def __repr__(self):
        return '<CategoryParamType %r>' % (self.Name, self.LimitUp)

class ComponentParam(db.Model):
    Id = db.Column(db.Integer, primary_key=True)
    ComponentId = db.Column(db.Integer, db.ForeignKey('component.Id'))
    CategoryParamTypeId = db.Column(db.Integer, db.ForeignKey('category_param_type.Id'))
    Note = db.Column(db.String(64), index=True, unique=False)

    def __repr__(slef):
        return '<ComponentParam %d, %d, %d, %r>' % (self.Id, self.ComponentId, self.CategoryParamTypeId, self.Note)

class BomElement(db.Model):
    Id = db.Column(db.Integer, primary_key=True)
    ComponentId = db.Column(db.Integer, db.ForeignKey('component.Id'))
    SchemeReference = db.Column(db.String(64), index=True, unique=False)
    BomId = db.Column(db.Integer, db.ForeignKey('bom.Id'))
    Mounted = db.Column(db.String(64), index=True, unique=False)
    Supplied = db.Column(db.String(64), index=True, unique=False)

    def __repr__(self):
        return '<BomElement %r>' % (self.SchemeReference)

class Board(db.Model):
    Id = db.Column(db.Integer, primary_key=True)
    Name = db.Column(db.String(64), index=True, unique=False)
    Revision = db.Column(db.String(64), index=True, unique=False)
    Particular = db.Column(db.String(64), index=True, unique=False)
    ProjectId = db.Column(db.Integer, db.ForeignKey('project.Id'))
    Note = db.Column(db.String(64), index=True, unique=False)

    def __repr__(self):
        return '<Board %r>' % (self.Id)

class Bom(db.Model):
    Id = db.Column(db.Integer, primary_key=True)
    BoardId = db.Column(db.Integer, db.ForeignKey('board.Id'))
    Revision = db.Column(db.String(64), index=True, unique=False)
    Date = db.Column(db.String(64), index=True, unique=False)
    Note = db.Column(db.String(64), index=True, unique=False)

    def __repr__(self):
        return '<Bom %r>' % (self.Note)

class Unit(db.Model):
    Id = db.Column(db.Integer, primary_key=True)
    Name = db.Column(db.String(64), index=True, unique=False)
    ShortName = db.Column(db.String(64), index=True, unique=False)
    Note = db.Column(db.String(64), index=True, unique=False)

    def __repr__(self):
        return '<Unit %r>' % (self.Name)

class Project(db.Model):
    Id = db.Column(db.Integer, primary_key=True)
    Name = db.Column(db.String(64), index=True, unique=False)
    Description = db.Column(db.String(64), index=True, unique=False)
    Note = db.Column(db.String(64), index=True, unique=False)

    def __repr__(self):
        return '<Project %r>' % (self.Name)