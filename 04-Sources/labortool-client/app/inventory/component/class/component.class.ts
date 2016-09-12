export class ComponentClass {
    ComponentId: number;
    ComponentName: string;
    ComponentManufacturer: number;
    ComponentPartNumber: string;
    ComponentDistributor: number;
    ComponentDistributorCode: string;
    ComponentPrice: number;
    ComponentCode: string;
    ComponentLocation: number;
    ComponentDatasheet: string;
    ComponentFootprint: number;
    ComponentCategory: number;
    ComponentNote: string;
}

export class JoinComponentClass {
    ComponentId: number;
    ComponentName: string;
    ManufacturerId: number;
    ManufacturerName: string;
    ManufacturerWebSite: string;
    ComponentPartNumber: string;
    DistributorId: number;
    DistributorName: string;
    DistributorWebSite: string;
    ComponentDistributorCode: string;
    ComponentPrice: number;
    ComponentCode: string;
    LocationId: number;
    LocationPosition: string;
    LocationContainer: string;
    LocationSubContainer: string;
    ComponentDatasheet: string;
    FootprintId: number;
    FootprintName: string;
    FootprintLink: string;
    CategoryId: number;
    CategoryName: string;
}