//////////////////////setup
module outdoorcover(){

    cylinder(h=100, r=30);
    
    translate([0,0,0])
    sphere(r = 30);
        
    translate([0,0,100])
    sphere(r = 30);
}   

module indoorcover(){
    scale([0.9,0.9,1])
    cylinder(h=100, r=30);
    
    translate([0,0,0])
    scale([0.9,0.9,0.9])
    sphere(r = 30);
        
    translate([0,0,100])
    scale([0.9,0.9,0.9])
    sphere(r = 30);
}

module subtracthalfcover(){
    translate([-40,-80,-40])
    cube([80, 80, 200]);
}

module vents(){
    translate([24,0,0])
    cube([3,40,40]);
    
    translate([18,0,0])
    cube([3,40,40]);
    
    translate([24,0,60])
    cube([3,40,40]);
    
    translate([18,0,60])
    cube([3,40,40]);
}

module outdoormountingplates(){
    translate([-40,0,-40])
    cube([80,3,180]);
}

module indoormountingplates(){
    scale([0.75,0.75,1])
    cylinder(h=100, r=30);
    
    translate([0,0,0])
    scale([0.75,0.75,0.75])
    sphere(r = 30);
        
    translate([0,0,100])
    scale([0.75,0.75,0.75])
    sphere(r = 30);
}

module screwholes(){
    translate([30,-10,130])
    rotate([-90,0,0])
    cylinder(h = 40, r = 1.5);
    
    translate([-30,-10,130])
    rotate([-90,0,0])
    cylinder(h = 40, r = 1.5);
    
    translate([30,-10,-30])
    rotate([-90,0,0])
    cylinder(h = 40, r = 1.5);
    
    translate([-30,-10,-30])
    rotate([-90,0,0])
    cylinder(h = 40, r = 1.5);
}
//////////////end

//////////////action
difference(){
    outdoorcover();
    indoorcover();
    subtracthalfcover();
    vents();
}

difference(){
    outdoormountingplates();
    indoormountingplates();
    screwholes();

}

