// float D_YAW = 0.1;
float lprop = 60.;
float dprop = 6;
float leg_len=100.;
float leg_wid=7;
int boxsize = 60;
float[] theta = {0.1, 0.3, 0.5, 1.2};
float body_x = 200;
float body_y = 200;
float axes_Ox;
float axes_Oy;
float angle_x = 1.0;
float angle_y = 0.0;
float angle_z = 0.0;
int ndata = 200;
float[] data1 = new float[ndata];
float[] data2 = new float[ndata];
float[] data3 = new float[ndata];


void setup(){
size(800, 600, P3D);
body_x = width/3.;
body_y = height/2.;
axes_Ox = width*2./3.;
axes_Oy = height*3.;
frameRate(30);
smooth();
stroke(#000000);
}


void draw()
{
  background(#DDDDDD);
  stroke(0);
  line(axes_Ox, height*0.9, width*0.95, height*0.9);
  line(axes_Ox, height*0.9, axes_Ox, height*0.65);
  line(axes_Ox, height*0.6, width*0.95, height*0.6);
  line(axes_Ox, height*0.6, axes_Ox, height*0.35);
  line(axes_Ox, height*0.3, width*0.95, height*0.3);
  line(axes_Ox, height*0.3, axes_Ox, height*0.05);
  float yaw = 0.;
  float pitch = 0.;
  float roll = 0.;
  float dtheta[] = {0.1, 0.2, 0.3, 0.4};
  int i;
  int data_frame = frameCount % ndata;
    
  if (mousePressed) {
   //yaw == 0.0 ? {yaw = mouseX; mx = } : yaw += D_YAW
   angle_x = -2*PI*(mouseY - body_y)/height;
   angle_y = 2*PI*(mouseX - body_x)/width;
  } 
  else {
    angle_z = atan2(mouseY - body_y, mouseX - body_x);
  }

  yaw = angle_z;
  pushMatrix();
  //angle += 0.05;
  translate(body_x, body_y);
  rotateX(angle_x);
  rotateY(angle_y);
  translate(-body_x, -body_y);

  drawDrone(yaw, pitch, roll);
  for (i=0; i<4; i++) {
  theta[i] += dtheta[i];
  }
  
  popMatrix();
  data1[data_frame] = theta[1];
  data2[data_frame] = yaw;
  data3[data_frame] = angle_y;
  
  for (i=0; i<ndata; i++) {
    int index = (data_frame + 1 + i) % ndata;
    stroke(#00AAAA);
    point(axes_Ox + i, height*0.3 - (0.2*height)*(data3[index]+PI)/(2*PI));
    stroke(#0000FF);
    point(axes_Ox + i, height*0.6 - (0.2*height)*(data2[index]+PI)/(2*PI));
    stroke(#FF0000);
    point(axes_Ox + i, height*0.9 - (0.1*height)*(1+cos(data1[index])));
  }

}

void drawDrone(float yaw, float pitch, float roll)
{
  int prop;
  float prop_center_x, prop_center_y;
  
  pushMatrix();
  translate(body_x, body_y);
  stroke(#AAAA00);
  line(0,0,0,0,0,100);
  stroke(0);
  rotate(yaw);
  rectMode(CENTER);
  fill(#55AA88);
  //noFill();
  box(boxsize, boxsize, boxsize/5.);
  translate(0,0,boxsize/10);
  fill(#333366);
  box(boxsize/2., boxsize/2., boxsize/5.);
//  rect(0, 0, boxsize, boxsize);
//  rect(0, 0, boxsize/2, boxsize/2);

  for (prop=0; prop<4; prop++){
    fill(100+30*prop,0,0);
    // rect( (leg_len + boxsize)/2*cos(prop*PI/2), (leg_len + boxsize)/2*sin(prop*PI/2), leg_len*cos(prop*PI/2) + leg_wid*sin(prop*PI/2), leg_len*sin(prop*PI/2) + leg_wid*cos(prop*PI/2));
    pushMatrix();
    translate( (leg_len + boxsize)/2*cos(prop*PI/2), (leg_len + boxsize)/2*sin(prop*PI/2));
    box(leg_len*cos(prop*PI/2) + leg_wid*sin(prop*PI/2), leg_len*sin(prop*PI/2) + leg_wid*cos(prop*PI/2), leg_wid);
    popMatrix();
    prop_center_x = (leg_len + boxsize/2)*cos(prop*PI/2);
    prop_center_y = (leg_len + boxsize/2)*sin(prop*PI/2);
    draw_propeller(prop_center_x, prop_center_y, pow(-1,prop)*theta[prop]);
  }
  popMatrix();
}

void draw_propeller(float prop_center_x, float prop_center_y, float theta){
  pushMatrix();
  translate(prop_center_x, prop_center_y);
  rotate(theta);
  ellipse(0, lprop/2,dprop,lprop);
  ellipse(0,-lprop/2,dprop,lprop);
  ellipse(0, 0, dprop, dprop);
  popMatrix();
}
