import matplotlib.pyplot as plt
import pandas as pd


def createGraph(fileName, picName):

    test = pd.read_csv(fileName)

    #   interpolation
    test = test.set_index('Size').reindex(range(test['Size'].min(), test['Size'].max() + 1))
    test = test.interpolate(method='spline', order=3).reset_index()

    # creating a plot
    plt.plot(test['Size'], test['schoolMult'], label="schoolMult", zorder=2, color='C1')
    plt.plot(test['Size'], test['dacMult'], label="dacMult", zorder=1, color='C0')
    plt.plot(test['Size'], test['karatsubaMult'], label="karatsubaMult", zorder=3, color="C2")

    plt.title('Multiplication Comparison')
    plt.xlabel('Size(digits)')
    plt.ylabel('Time(ms)')
    plt.legend()
    plt.savefig(picName, dpi=300)
    plt.clf()


createGraph("../data/testResults500.csv", "../graphs/SmallGraph.png")     # test on numbers up to 500
createGraph("../data/testResults10000.csv", "../graphs/MainGraph.png")    # test on numbers up to 10 000
