package yakupov;

/**
 * Class of Matrix
 */
public class Matrix {
    private int h, w;
    private double[] a = null;

    /**
     * Constructor
     * @param h Number of rows
     * @param w Number of columns
     */
    Matrix(int h, int w) {
        this.h = h;
        this.w = w;
        a = new double[h*w];
        for (int i = 0; i < h*w; i++) {
            a[i] = 0;
        }
    }

    /**
     * Get number of rows
     * @return Number of rows
     */
    public int getH() {
        return h;
    }

    /**
     * Get number of columns
     * @return Number of columns
     */
    public int getW() {
        return w;
    }

    /**
     * Calculates coords into position in array
     * @param i First coord
     * @param j Second coord
     * @return Position in array
     */
    private int ind(int i, int j) {
        return i * getW() + j;
    }

    /**
     * Gets value by coords
     * @param i First coord
     * @param j Second coord
     * @return value
     */
    public double get(int i, int j) {
        return a[ind(i, j)];
    }

    /**
     * Sets value by coords
     * @param i First coord
     * @param j Second coord
     * @param value Value
     */
    public void set(int i, int j, double value) {
        a[ind(i, j)] = value;
    }

    /**
     * Multiply two matrixes(static member)
     * @param m1 First matrix
     * @param m2 Second matrix
     * @return Result matrix
     */
    public static Matrix multi(Matrix m1, Matrix m2) {
        int hRes = m1.getH();
        int wRes = m2.getW();

        if (m1.getW() != m2.getH()) {
            System.err.println("Can't do multiplication cause of bad sizes");
            return new Matrix(1, 1);
        }

        int count = m1.getW();
        Matrix res = new Matrix(hRes, wRes);
        for (int i = 0; i < hRes; i++)
            for (int j = 0; j < wRes; j++)
                for (int k = 0; k < count; k++) {
                    res.set(i, j, res.get(i, j) + m1.get(i, k) * m2.get(k, j));
                }
        return res;
    }

    /**
     * Transponents matrix
     */
    public void tranponent() {
        double[] T = new double[getH() * getW()];
        for (int i = 0; i < getH(); i++)
            for (int j = 0; j < getW(); j++) {
                T[ind(j, i)] = a[ind(i, j)];
            }
        a = T;
    }
    ////
    public static Matrix multiTransp(Matrix m1, Matrix tr) {
        int hRes = m1.getH();
        int wRes = tr.getW();

        if (m1.getW() != tr.getH()) {
            System.err.println("Can't do multiplication cause of bad sizes");
            return new Matrix(1, 1);
        }

        int count = m1.getW();
        Matrix res = new Matrix(hRes, wRes);
        for (int i = 0; i < hRes; i++)
            for (int j = 0; j < wRes; j++)
                for (int k = 0; k < count; k++) {
                    res.set(i, j, res.get(i, j) + m1.get(i, k) * tr.get(j, k));
                }
        return res;
    }
}
