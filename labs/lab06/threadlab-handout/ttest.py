import subprocess
import multiprocessing
import random
import argparse
import json
import time

parser = argparse.ArgumentParser(description='Run tests on thread assigments.')
parser.add_argument('--no-pi', action='store_false', dest="pi",
                    help='don\'t run tests on the pi executable')
parser.add_argument('--no-sem', action='store_false', dest="sem",
                    help='don\'t run tests on the sem executable')
parser.add_argument('--grade', action='store_true', dest="grade",
                    help='generate the output for gradescope')


grade = {
    "output": "",
    "tests": [
        {
            "score": 0.0,
            "max_score": 3.0,
            "name": "Parallel pie",
            "output": "",
            "visibility": "visible"
        },
        {
            "score": 0.0,
            "max_score": 6.0,
            "name": "Semaphores",
            "output": "",
            "visibility": "visible"
        },
    ]
}

args = parser.parse_args()


n_cores = multiprocessing.cpu_count()
DEBUG = 0

result = {}

def make(args):
    argv = ["make"]
    if args is None:
        args = []
    if not isinstance(args, list):
        args = [args]
    argv.extend(args)
    if DEBUG: print(f"running: {argv}")
    proc = subprocess.run(argv, capture_output=True, shell=False, timeout=30)
    stdout = proc.stdout.decode("utf-8")
    stderr = proc.stderr.decode("utf-8")
    if proc.returncode != 0:
        print("Error making:")
        print(f"Output:\n{stdout}")
        print(f"Error:\n{stderr}")
    if DEBUG:
        print(f"Debug output:\n{stdout}")



def run(exec, args=None):
    if args is None:
        args = []
    argv = [exec]
    if not isinstance(args, list):
        args = [args]
    argv.extend(args)
    try:
        start_time = time.time()
        proc = subprocess.run(argv, capture_output=True, shell=False, timeout=120)
        end_time = time.time()
        execution_time = end_time - start_time
        stdout = proc.stdout.decode("utf-8")
        stderr = proc.stderr.decode("utf-8")
        if proc.returncode != 0:
            print("Error running:")
            print(f"{stderr}")
        if DEBUG:
            print(f"Debug output:\n{stdout}")
    except subprocess.TimeoutExpired:
        stdout = ""
        stderr = ""
        execution_time = 100000
    return stdout, stderr, execution_time


if(args.pi):
    runtimes = []
    pass_pi_correctness = True
    pass_pi_timeliness = True
    for i in [1,2,4]:
        s = "s" if i>1 else ""
        print(f"Calculating PI with {i} thread{s}...")
        make(["clean"])
        make([f"CFLAGS=-DNUM_THREADS={i} -DNUM_POINTS=1000000000LU -DDEBUG=0", "pi"])
        stdout, stderr, runtime = run("./pi")
        PI_estimate = float(stdout.split(" ")[-1])
        runtimes.append(runtime)
        print(f"Executed in {runtime} and calculated PI as {PI_estimate}\n")
        if(PI_estimate<3.14 or PI_estimate > 3.15):
            print(f"Something doesn't look good with that estimate 🤔\n")
            pass_pi_correctness = False
        if i>1:
            if i <= n_cores:
                if(runtimes[-1]/runtimes[-2] >= 1):
                    print(f"More threads not faster? 🤔\n")
                    pass_pi_timeliness = False
                elif(runtimes[-1]/runtimes[-2] >= 0.7):
                    print(f"Faster, but not much? 🤔, I'm blaming Gradescope\n")
                    # pass_pi_timeliness = False
            elif (runtimes[-1]/runtimes[-2] >= 0.9):
                print(f"More threads not much faster? 🤔")
                print(f"Maybe I ran out of CPUs?")
                print(f"I'm using {i} threads on {n_cores} CPU cores!")
    if not pass_pi_correctness:
        grade["tests"][0]["score"] = 0.0
    elif not pass_pi_timeliness:
        grade["tests"][0]["score"] = 1.5
    else:
        grade["tests"][0]["score"] = 3.0

   
if (args.sem):
    print(f"Running sem...")
    i=0
    n_clients = 1000
    n_washing_machines = 4
    n_driers = 2
    n_folding_stations = 2

    print(f"Making sem...")
    make(["clean"])
    make([f"CFLAGS=-DN_CLIENTS={n_clients} -DN_MACHINES={n_washing_machines} -DN_DRIERS={n_driers} -DN_FOLDERS={n_folding_stations} -DDEBUG=0", "sem"])
    make([f"CFLAGS=-DN_CLIENTS={n_clients} -DN_MACHINES={n_washing_machines} -DN_DRIERS={n_driers} -DN_FOLDERS={n_folding_stations} -DDEBUG=0", "sem_solution"])

    print(f"Running program...")
    _, _, native_time = run("./sem_solution")
    stdout, stderr, execution_time = run("./sem")

    print(f"Collecting output...")
    fail = False
    results={}
    results["washing"] = 0
    results["drying"] = 0
    results["folding"] = 0
    for output in stdout.split("\n"):
        if (len(output)!=0):
            lst = output.split(":")
            client = int(lst[0])
            action = lst[1].strip().lower()
            completed = lst[-1].strip().lower()
            if (completed == action):
                results[action] = results[action] + 1
            else:
                results[action] = results[action] - 1
        if (results["washing"] > n_washing_machines):
            print(f"It looks like the washing machines are being overused!!")
            fail = True
        if (results["drying"] > n_driers):
            print(f"It looks like the driers machines are being overused!!")
            fail = True
        if (results["folding"] > n_folding_stations):
            print(f"It looks like the folding stations are being overused!!")
            fail = True

    if (not fail):
        print("Looks good :)")
        print(f"Native semaphores took {native_time} seconds to run")
        print(f"Your program took {execution_time} seconds to run")
        grade["tests"][1]["score"] = 6.0
        # print(execution_time)
        if(execution_time > 10*native_time):
            print("But your performance sucks! :(\nMake sure you are not keeping the CPU busy on loops!")
            grade["tests"][1]["score"] = 3.0
    else:
        print("Something is not right!")
        grade["tests"][1]["score"] = 0.0

    with open("stdout.txt", "w") as f:
        f.write(stdout)
    with open("stderr.txt", "w") as f:
        f.write(stderr)

if args.grade:
    with open("grade.json", "w") as f:
        f.write(json.dumps(grade, indent=4))