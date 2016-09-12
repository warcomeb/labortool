export class JoinCatParamTypeClass {
    CategoryParamTypeId: number;
    CategoryParamTypeName: string;
    CategoryId: number;
    CategoryName: string;
    UnitId: number;
    UnitName: string;
    CategoryParamTypeOrder: string;
}

export class CategoryParamTypeClass {
    CategoryParamTypeId: number;
    CategoryParamTypeName: string;
    CategoryParamTypeCategory: number;
    CategoryParamTypeUnit: number;
    CategoryParamTypeOrder: string;
    CategoryParamTypeNote: string;
}

export class JoinUnitClass {
    UnitId: number;
    UnitShortName: string;
}