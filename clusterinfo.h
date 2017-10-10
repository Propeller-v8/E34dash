#ifndef CLUSTERINFO_H
#define CLUSTERINFO_H

#include <QObject>
#include <QByteArray>
#include <QString>

typedef struct rec_value
{
	uintptr_t value;
	const QString name;
} info_value_t;

typedef struct property {
	const char *prop;
	const QString name;
	unsigned addr;
	unsigned size;
	unsigned mask;
	const struct rec_value *values;
	bool complementary;
} info_property_t;

class ClusterInfo : public QObject
{
	Q_OBJECT

public:
	ClusterInfo();

	void parseData();
	void updateProperties();
	void updateSimple();

	unsigned char *getDump( unsigned offset = 0 ) { return m_data + offset; }
	unsigned getData( unsigned addr, unsigned mask = 0xFF );
	void setData( unsigned addr, unsigned val, unsigned mask = 0xFF );

	int setVIN( const QString &vin );
	void setOdometer( unsigned milage );
	void setTank( int index );
	void setTempSensor( int index );
	void setPartNum( unsigned num );
	void setCodeNum( unsigned num );

	unsigned m_size;

	QString m_vin;
	QString m_partnum;
	QString m_code;
	long m_odometer;
	unsigned m_tankcurve;
	unsigned m_tempcurve;

private:
	unsigned char m_data[256];

signals:
	void updateDump();
	void propertiesReset();
	void addProperty( const info_property_t *rec, uintptr_t value, const info_value_t *known = NULL );
};

#endif // CLUSTERINFO_H