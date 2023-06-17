class Transformation {
public:
    class Vec {
            double v[3];
        public:
            Vec() { v[0]=v[1]; v[2]=1; }
            Vec(double x, double y) { v[0]=x; v[1]=y; v[2]=1; }
            double& operator[](int n) { return v[n]; }
    };

private:
    class Mat{
        Vec A[3];
    public:
        Vec& operator[](int n) { return A[n]; }
        friend Mat operator*(Mat& A, Mat& B) {
            Mat C;
            for(int i=0;i<3;i++)
                for(int j=0;j<3;j++) {
                    C[i][j]=0;
                    for(int k=0;k<3;k++)
                        C[i][j]+=A[i][k]*B[k][j];
            }
            return C;
        }

        friend Vec operator*(Mat& A, Vec& v) {
            Vec r;
            for(int i=0;i<3;i++) {
            r[i]=0;
                for(int j=0;j<3;j++)
                    r[i]+=A[i][j]*v[j];
            }
            return r;
        }

        Mat& operator*=(Mat& B) {
            *this=*this*B;
            return *this;
        }

    };

    Line* line;
    Mat T;

    Mat Identity() {
        Mat A;
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                A[i][j] = 1 ? i==j : 0;
        return A;
    }

    Mat translate(double dx, double dy) {
        Mat T = Identity();
        T[0][2]=dx;
        T[1][2]=dy;
        return T;
    }

    Mat scale(double alpha, double beta) {
        Mat Sc=Identity();
        Sc[0][0]=alpha;
        Sc[1][1]=beta;
        return Sc;
    }

public:
    Transformation(Line* line) {this->line = line; this->T = Identity();}

    void TranslateLine() {
        int dx, dy;
        cout << "Enter the Transform Value x, y: ";
        cin >> dx >> dy;
        Mat T2 = this->translate(dx,dy);
        this->T *= T2;

        Vec* startPoints = new Vec(line->xs, line->ys);
        line->xs = (T * (*startPoints))[0];
        line->ys = (T * (*startPoints))[1];

        Vec* endPoints = new Vec(line->xe, line->ye);
        line->xe = (T * (*endPoints))[0];
        line->ye = (T * (*endPoints))[1];

        this->line->Draw();
    }

    void ScaleLine() {
        int alpha, beta;
        cout << "Enter the Scale Value alpha, beta: ";
        cin >> alpha >> beta;
        // Calculate the center point of the line
        double centerX = (line->xs + line->xe) / 2.0;
        double centerY = (line->ys + line->ye) / 2.0;

        // Translate the line so that its center point is at the origin
        Mat T1 = this->translate(-centerX, -centerY);

        // Scale the line around the origin
        Mat S = this->scale(alpha, beta);

        // Translate the line back to its original position
        Mat T2 = this->translate(centerX, centerY);
        Mat x1 = (T2 * S);
        Mat x2 = x1 * T1;
        // Update the transformation matrix by multiplying the translation, scaling, and inverse translation matrices in the correct order
        this->T *= x2;

        Vec* startPoints = new Vec(line->xs, line->ys);
        line->xs = (T * (*startPoints))[0];
        line->ys = (T * (*startPoints))[1];

        Vec* endPoints = new Vec(line->xe, line->ye);
        line->xe = (T * (*endPoints))[0];
        line->ye = (T * (*endPoints))[1];

        this->line->Draw();
    }

};


