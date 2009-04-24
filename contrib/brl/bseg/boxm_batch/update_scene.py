import boxm_batch;
boxm_batch.register_processes();
boxm_batch.register_datatypes();

class dbvalue:
  def __init__(self, index, type):
    self.id = index    # unsigned integer
    self.type = type   # string

print("Creating a Scene");
boxm_batch.init_process("boxmCreateSceneProcess");
boxm_batch.set_params_process("createScene.xml");
boxm_batch.run_process();
(scene_id, scene_type) = boxm_batch.commit_output(0);
scene = dbvalue(scene_id, scene_type);

import glob
import random

image_fnames = glob.glob("Z:/video/dec/CapitolSiteHigh/video/*.png");
camera_fnames = glob.glob("Z:/video/dec/CapitolSiteHigh/cameras_KRT/*.txt");

min_range = 10;
last_i = -min_range;
nframes = 145;

for x in range(125,nframes,1):
  i = random.randint(0,254);
  # try, try again if this frame is too close to the last
  while (abs(i - last_i) < min_range):
    i = random.randint(0,254);
  last_i = i;
  
  print("Loading Camera");
  boxm_batch.init_process("vpglLoadPerspectiveCameraProcess");
  boxm_batch.set_input_string(0,camera_fnames[i]);
  boxm_batch.run_process();
  (id,type) = boxm_batch.commit_output(0);
  cam = dbvalue(id,type);
  
  print("Loading Image");
  boxm_batch.init_process("vilLoadImageViewProcess");
  boxm_batch.set_input_string(0,image_fnames[i]);
  boxm_batch.run_process();
  (id,type) = boxm_batch.commit_output(0);
  image = dbvalue(id,type);
  
  print("Updating Scene");
  boxm_batch.init_process("boxmUpdateProcess");
  boxm_batch.set_input_from_db(0,image);
  boxm_batch.set_input_from_db(1,cam);
  boxm_batch.set_input_from_db(2,scene);
  boxm_batch.set_input_unsigned(3,0);
  boxm_batch.run_process();

print("Saving raw");
boxm_batch.init_process("boxmSaveOccupancyRawProcess");
boxm_batch.set_input_from_db(0,scene);
boxm_batch.set_input_string(1,"./block_raw");
boxm_batch.set_input_unsigned(2, 0);
boxm_batch.run_process();

