#!/usr/bin/env python#

import sys
import subprocess
from subprocess import call
#import pip

#path = sys.argv[1:]
path = "/Users/nchronas/Documents/repos/delfiPQ/workspace7/"

print "Workspace dir:", path

print "Cloning repos"

cmd = "git clone https://github.com/nchronas/ADB_software.git"
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

cmd = "git clone https://github.com/nchronas/EPS_software.git"
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

cmd = "git clone https://github.com/nchronas/OBC_software.git"
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

cmd = "git clone https://github.com/nchronas/ADCS_software.git"
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

cmd = "git clone https://github.com/nchronas/RED_software.git"
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

cmd = "git clone https://github.com/nchronas/COMMS_software.git"
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

cmd = "git clone https://github.com/nchronas/MPP_software.git"
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()


cmd = "git clone https://github.com/nchronas/PQ9_bus_software.git"
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

cmd = "git clone https://github.com/nchronas/INA226.git"
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

cmd = "git clone https://github.com/nchronas/TMP100.git"
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

cmd = "git clone https://github.com/nchronas/MB85RS256A.git"
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

cmd = "git clone https://github.com/nchronas/LTC2942.git"
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

cmd = "git clone https://github.com/nchronas/AD5235.git"
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

print "Making RED project"

working_dir = path + "RED_software"

pq9_path = path + "PQ9_bus_software/"

print "Creating folders"

call(["mkdir", "ttc"], cwd=working_dir)

print "Creating symlinks"

folder = "RED_software/"

f = pq9_path + "delfiPQ/RED/HAL/RED_Board.h"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "delfiPQ/RED/HAL/RED_Board.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

folder = "RED_software/ttc/"

f = pq9_path + "delfiPQ/HAL/hal_functions.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "delfiPQ/RED/HAL/hal_subsystem.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "delfiPQ/RED/devices.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "delfiPQ/RED/fm.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "delfiPQ/RED/housekeeping.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "delfiPQ/RED/parameters.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "delfiPQ/RED/subsystem_pool.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "delfiPQ/RED/subsystem.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "delfiPQ/OSAL/osal.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "delfiPQ/packet_engine.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "delfiPQ/satellite.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "delfiPQ/PQ9_bus_engine.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()


f = pq9_path + "core/function_management_service.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "core/housekeeping_service.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "core/packet_stats.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "core/packet_utilities.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "core/ping_service.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "core/pkt_pool.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "core/verification_service.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "core/queue.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

print "Input to ccs directories"
print pq9_path + "delfiPQ/RED"
print pq9_path + "delfiPQ/RED/HAL"
print pq9_path + "delfiPQ/HAL"
print pq9_path + "delfiPQ/OSAL"
print pq9_path + "delfiPQ"
print pq9_path + "core"
print pq9_path + "services"



print "Making ADB project"

working_dir = path + "ADB_software"

pq9_path = path + "PQ9_bus_software/"

print "Creating folders"

call(["mkdir", "libs"], cwd=working_dir)
call(["mkdir", "ttc"], cwd=working_dir)

print "Creating symlinks"

folder = "ADB_software/"

f = pq9_path + "delfiPQ/ADB/HAL/ADB_Board.h"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "delfiPQ/ADB/HAL/ADB_Board.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

folder = "ADB_software/ttc/"

f = pq9_path + "delfiPQ/HAL/hal_functions.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "delfiPQ/ADB/HAL/hal_subsystem.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "delfiPQ/ADB/devices.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "delfiPQ/ADB/housekeeping.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "delfiPQ/ADB/parameters.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "delfiPQ/ADB/subsystem_pool.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "delfiPQ/ADB/subsystem.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "delfiPQ/OSAL/osal.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "delfiPQ/packet_engine.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "delfiPQ/satellite.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "delfiPQ/PQ9_bus_engine.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()


f = pq9_path + "core/function_management_service.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "core/housekeeping_service.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "core/packet_stats.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "core/packet_utilities.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "core/ping_service.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "core/pkt_pool.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "core/verification_service.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "core/queue.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "core/testing.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

folder = "ADB_software/libs/"

f = path + "TMP100/TMP100.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = path + "INA226/INA226.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

print "Input to ccs directories"
print pq9_path + "delfiPQ/ADB"
print pq9_path + "delfiPQ/ADB/HAL"
print pq9_path + "delfiPQ/HAL"
print pq9_path + "delfiPQ/OSAL"
print pq9_path + "delfiPQ"
print pq9_path + "core"
print path + "INA226"
print path + "TMP100"



print "Making EPS project"

working_dir = path + "EPS_software"

pq9_path = path + "PQ9_bus_software/"

print "Creating folders"

call(["mkdir", "libs"], cwd=working_dir)
call(["mkdir", "ttc"], cwd=working_dir)

print "Creating symlinks"

folder = "EPS_software/"

f = pq9_path + "delfiPQ/EPS/HAL/EPS_Board.h"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "delfiPQ/EPS/HAL/EPS_Board.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()


folder = "EPS_software/ttc/"

f = pq9_path + "delfiPQ/HAL/hal_functions.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "delfiPQ/EPS/HAL/hal_subsystem.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "delfiPQ/EPS/devices.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "delfiPQ/EPS/fm.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "delfiPQ/EPS/housekeeping.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "delfiPQ/EPS/parameters.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "delfiPQ/EPS/safety_check.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "delfiPQ/EPS/subsystem_pool.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "delfiPQ/EPS/subsystem.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "delfiPQ/OSAL/osal.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "delfiPQ/packet_engine.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "delfiPQ/PQ9_bus_engine.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "delfiPQ/satellite.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()


f = pq9_path + "core/function_management_service.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "core/housekeeping_service.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "core/packet_stats.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "core/packet_utilities.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "core/ping_service.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "core/pkt_pool.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "core/verification_service.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "core/queue.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "core/testing.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()


folder = "EPS_software/libs/"
f = path + "TMP100/TMP100.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = path + "INA226/INA226.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = path + "LTC2942/LTC2942.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = path + "MB85RS256A/MB85RS256A.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

print "Input to ccs directories"
print pq9_path + "delfiPQ/EPS"
print pq9_path + "delfiPQ/EPS/HAL"
print pq9_path + "delfiPQ/HAL"
print pq9_path + "delfiPQ/OSAL"
print pq9_path + "delfiPQ"
print pq9_path + "core"
print path + "INA226"
print path + "TMP100"
print path + "MB85RS256A"
print path + "LTC2942"



print "Making OBC project"

working_dir = path + "OBC_software"

pq9_path = path + "PQ9_bus_software/"

print "Creating folders"

call(["mkdir", "libs"], cwd=working_dir)
call(["mkdir", "ttc"], cwd=working_dir)

print "Creating symlinks"

folder = "OBC_software/"

f = pq9_path + "delfiPQ/OBC/HAL/OBC_Board.h"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "delfiPQ/OBC/HAL/OBC_Board.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

folder = "OBC_software/ttc/"

f = pq9_path + "delfiPQ/HAL/hal_functions.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "delfiPQ/OBC/HAL/hal_subsystem.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "delfiPQ/OBC/devices.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "delfiPQ/OBC/fm.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "delfiPQ/OBC/housekeeping.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "delfiPQ/OBC/parameters.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "delfiPQ/OBC/rf_packet.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "delfiPQ/OBC/subsystem_pool.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "delfiPQ/OBC/subsystem.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()


f = pq9_path + "delfiPQ/OSAL/osal.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "delfiPQ/packet_engine.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "delfiPQ/PQ9_bus_engine.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "delfiPQ/satellite.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()


f = pq9_path + "core/en_data_service.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "core/function_management_service.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "core/housekeeping_service.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "core/packet_stats.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "core/packet_utilities.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "core/ping_service.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "core/pkt_pool.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "core/verification_service.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "core/queue.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "core/testing.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()


folder = "OBC_software/libs/"
f = path + "TMP100/TMP100.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = path + "INA226/INA226.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = path + "MB85RS256A/MB85RS256A.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

print "Input to ccs directories"
print pq9_path + "delfiPQ/OBC"
print pq9_path + "delfiPQ/OBC/HAL"
print pq9_path + "delfiPQ/HAL"
print pq9_path + "delfiPQ/OSAL"
print pq9_path + "delfiPQ"
print pq9_path + "core"
print path + "INA226"
print path + "TMP100"
print path + "MB85RS256A"



print "Making ADCS project"

working_dir = path + "ADCS_software"

pq9_path = path + "PQ9_bus_software/"

print "Creating folders"

call(["mkdir", "libs"], cwd=working_dir)
call(["mkdir", "ttc"], cwd=working_dir)

print "Creating symlinks"

folder = "ADCS_software/"

f = pq9_path + "delfiPQ/ADCS/HAL/ADCS_Board.h"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "delfiPQ/ADCS/HAL/ADCS_Board.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

folder = "ADCS_software/ttc/"

f = pq9_path + "delfiPQ/HAL/hal_functions.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "delfiPQ/ADCS/HAL/hal_subsystem.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()
f = pq9_path + "delfiPQ/ADCS/devices.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "delfiPQ/ADCS/fm.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "delfiPQ/ADCS/housekeeping.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "delfiPQ/ADCS/parameters.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "delfiPQ/ADCS/subsystem_pool.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "delfiPQ/ADCS/subsystem.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()


f = pq9_path + "delfiPQ/OSAL/osal.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "delfiPQ/packet_engine.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "delfiPQ/PQ9_bus_engine.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "delfiPQ/satellite.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()


f = pq9_path + "core/function_management_service.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "core/housekeeping_service.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "core/packet_stats.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "core/packet_utilities.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "core/ping_service.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "core/pkt_pool.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "core/verification_service.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "core/queue.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "core/testing.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()


folder = "ADCS_software/libs/"
f = path + "TMP100/TMP100.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = path + "INA226/INA226.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = path + "MB85RS256A/MB85RS256A.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

print "Input to ccs directories"
print pq9_path + "delfiPQ/ADCS"
print pq9_path + "delfiPQ/ADCS/HAL"
print pq9_path + "delfiPQ/HAL"
print pq9_path + "delfiPQ/OSAL"
print pq9_path + "delfiPQ"
print pq9_path + "core"
print path + "INA226"
print path + "TMP100"
print path + "MB85RS256A"


print "Making MPP project"

working_dir = path + "MPP_software"

pq9_path = path + "PQ9_bus_software/"

print "Creating folders"

call(["mkdir", "libs"], cwd=working_dir)
call(["mkdir", "ttc"], cwd=working_dir)

print "Creating symlinks"

folder = "MPP_software/"

f = pq9_path + "delfiPQ/MPP/HAL/MPP_Board.h"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "delfiPQ/MPP/HAL/MPP_Board.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

folder = "MPP_software/ttc/"

f = pq9_path + "delfiPQ/HAL/hal_functions.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "delfiPQ/MPP/HAL/hal_subsystem.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()
f = pq9_path + "delfiPQ/MPP/devices.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "delfiPQ/MPP/fm.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "delfiPQ/MPP/housekeeping.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "delfiPQ/MPP/parameters.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "delfiPQ/MPP/subsystem_pool.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "delfiPQ/MPP/subsystem.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()


f = pq9_path + "delfiPQ/OSAL/osal.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "delfiPQ/packet_engine.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "delfiPQ/PQ9_bus_engine.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "delfiPQ/satellite.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()


f = pq9_path + "core/function_management_service.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "core/housekeeping_service.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "core/packet_stats.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "core/packet_utilities.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "core/ping_service.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "core/pkt_pool.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "core/verification_service.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "core/queue.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "core/testing.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()


folder = "MPP_software/libs/"
f = path + "TMP100/TMP100.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = path + "INA226/INA226.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = path + "MB85RS256A/MB85RS256A.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = path + "AD5235/AD5235.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

print "Input to ccs directories"
print pq9_path + "delfiPQ/MPP"
print pq9_path + "delfiPQ/MPP/HAL"
print pq9_path + "delfiPQ/HAL"
print pq9_path + "delfiPQ/OSAL"
print pq9_path + "delfiPQ"
print pq9_path + "core"
print path + "INA226"
print path + "TMP100"
print path + "MB85RS256A"
print path + "AD5235"




print "Making COMMS project"

working_dir = path + "COMMS_software"

pq9_path = path + "PQ9_bus_software/"

print "Creating folders"

call(["mkdir", "libs"], cwd=working_dir)
call(["mkdir", "ttc"], cwd=working_dir)

print "Creating symlinks"

folder = "COMMS_software/"

f = pq9_path + "delfiPQ/COMMS/HAL/COMMS_Board.h"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "delfiPQ/COMMS/HAL/COMMS_Board.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

folder = "COMMS_software/ttc/"

f = pq9_path + "delfiPQ/HAL/hal_functions.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "delfiPQ/COMMS/HAL/hal_subsystem.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "delfiPQ/COMMS/devices.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "delfiPQ/COMMS/fm.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "delfiPQ/COMMS/housekeeping.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "delfiPQ/COMMS/parameters.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "delfiPQ/COMMS/rf_packet.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "delfiPQ/COMMS/subsystem_pool.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "delfiPQ/COMMS/subsystem.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()


f = pq9_path + "delfiPQ/OSAL/osal.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "delfiPQ/packet_engine.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "delfiPQ/PQ9_bus_engine.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "delfiPQ/satellite.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()


f = pq9_path + "core/en_data_service.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "core/function_management_service.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "core/housekeeping_service.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "core/packet_utilities.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "core/packet_stats.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "core/ping_service.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "core/pkt_pool.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "core/verification_service.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "core/queue.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

f = pq9_path + "core/testing.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()


folder = "COMMS_software/libs/"
f = path + "TMP100/TMP100.c"
cmd = "ln -s " + f + " " + folder
pipe = subprocess.Popen(cmd, shell=True)
pipe.wait()

print "Input to ccs directories"
print pq9_path + "delfiPQ/COMMS"
print pq9_path + "delfiPQ/COMMS/HAL"
print pq9_path + "delfiPQ/HAL"
print pq9_path + "delfiPQ/OSAL"
print pq9_path + "delfiPQ"
print pq9_path + "core"
print path + "TMP100"




print "Install pyserial, you need to have pip"
print """pip.main(['install', "pyserial"])"""

print "Dont forget to:"
print "add the ti-rtos kernel (import from simplelink and add build dependency)"
print "Add c99 flag"
print "Modify simplelink uart driverlib for pq9 packet handling"
