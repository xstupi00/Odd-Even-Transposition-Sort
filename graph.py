import subprocess
import matplotlib.pyplot as plt

def rewrite_hostfile(n):
    with open("hostfile", 'r+') as f:
        _ = f.read()
        f.seek(0, 0)
        f.write("localhost slots=" + str(n))

def rewrite_results(results):
    with open("results.txt", 'r+') as f:
        _ = f.read()
        f.seek(0, 0)
        for result in results:
            f.write(str(result) + '\n')


def create_graph(elapsed_time, samples):
    fig, ax = plt.subplots()
    ax.plot(samples, elapsed_time[0], linestyle='-', marker='o', color='b')
    ax.plot(samples, elapsed_time[1], linestyle='-', marker='o', color='r')
    ax.set(xlabel='n - points count', ylabel='time (us)',
           title='Line-of-Sight')
    ax.grid()
    fig.savefig("plot.png")
    plt.show()

def plot_graph():
    elapsed_times = []
    for n in range(1, 50, 2):
        sub_results = []
        rewrite_hostfile(n)
        for i in range(1, 8):
            output = subprocess.check_output(['./test.sh', str(n)])
            if i != 0:
                sub_results.append(float(output.decode("utf-8").split("\n")[1]))
        elapsed_times.append(min(sub_results))
        rewrite_results(elapsed_times)
    create_graph(elapsed_times, range(1, 50, 2))

if __name__ == '__main__':
    create_graph([[8.0, 23.0, 19.0, 19.0, 18.0, 19.0, 16.0, 67.0, 67.0, 253.0, 91.0, 275.0, 272.0, 270.0, 330.0, 343.0, 327.0, 334.0, 235.0, 235.0, 241.0, 235.0, 231.0, 359.0, 371.0, 373.0, 354.0, 393.0, 397.0], [7.0, 10.0, 8.0, 32.0, 32.0, 18.0, 16.0, 66.0, 67.0, 87.0, 85.0, 95.0, 93.0, 34.0, 34.0, 126.0, 122.0, 131.0, 128.0, 151.0, 154.0, 170.0, 168.0, 176.0, 176.0, 194.0, 194.0, 203.0, 200.0]], range(2,31,1))
