public class ComplexNumber {
	double RealPart;
	double ImaginaryPart;
	public static final double EPSILON = 0.001;
	
	public ComplexNumber(double RealPart, double ImaginaryPart){
		this.RealPart = RealPart;
		this.ImaginaryPart = ImaginaryPart;
	}
	
	public double getRealPart() {
		return	this.RealPart;
	}
	
	public double getImaginaryPart() {
		return	this.ImaginaryPart;
	}
	
	public double getRadius() {
		return Math.sqrt(this.RealPart*this.RealPart + this.ImaginaryPart*this.ImaginaryPart);
	}

	public double getArgument() {
		return Math.atan2(ImaginaryPart, RealPart);
                                            
	}
	
	public boolean almostEquals(ComplexNumber other) {
		return Math.abs(this.getRadius() - other.getRadius()) < ComplexNumber.EPSILON;
	}
	
	public static ComplexNumber fromPolarCoordinates(double radius, double argument) {
		return new ComplexNumber(radius*Math.cos(argument), radius*Math.sin(argument));
	}
	
	public ComplexNumber plus(ComplexNumber other) {
		return new ComplexNumber(this.RealPart+other.RealPart, this.ImaginaryPart+other.ImaginaryPart);
	}
	
	public ComplexNumber minus(ComplexNumber other) {
		return new ComplexNumber(this.RealPart-other.RealPart, this.ImaginaryPart-other.ImaginaryPart);
	}
	
	ComplexNumber times(ComplexNumber other) {
		double r1 = this.getRadius(), r2 = other.getRadius();
		double theta1 = this.getArgument(), theta2 = other.getArgument();
		return ComplexNumber.fromPolarCoordinates(r1*r2, theta1+theta2);
	}

	ComplexNumber divide(ComplexNumber other) {
		double r1 = this.getRadius(), r2 = other.getRadius();
		double theta1 = this.getArgument(), theta2 = other.getArgument();
		return ComplexNumber.fromPolarCoordinates(r1/r2, theta1-theta2);
	}

}
