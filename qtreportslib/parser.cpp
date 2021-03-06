#include <QFile>
#include <QLabel>
#include <QTextBrowser>
#include <QVBoxLayout>
#include "parser.hpp"

namespace qtreports {
    namespace detail {

        Parser::Parser() {}

        Parser::~Parser() {}

        bool	Parser::parse( const QString & path ) {
            if( !QFile::exists( path ) ) {
                m_lastError = "The file not exists";
                return false;
            }

            QFile file( path );
            file.open( QIODevice::OpenModeFlag::ReadOnly | QIODevice::Text );
            if( !file.isOpen() ) {
                m_lastError = "The file can not be opened";
                return false;
            }

            return parseReport( file.readAll() );
        }

        bool	Parser::parseReport( const QString & text ) {
            QXmlStreamReader reader( text );
            while( !reader.atEnd() ) {
                reader.readNext();
                if( reader.isStartDocument() ) {
                    continue;
                }

                if( reader.isStartElement() ) {
                    auto name = reader.name();
                    if( name == "detail" ) {
                        auto detailData = reader.readElementText( QXmlStreamReader::ReadElementTextBehaviour::IncludeChildElements );
                        auto result = parseDetail( detailData );
                        if( !result ) {
                            break;
                        }
                    }
                    else if( name == "element2" ) {
                        reader.readNext();
                        //reader.text().toString();
                    }
                }
                reader.readNext();
            }

            if( reader.hasError() ) {
                m_lastError = reader.errorString();
                //return false;
            }

            createWidget();
            return true;
        }

        bool	Parser::parseDetail( const QString & text ) {
            QXmlStreamReader reader( text );
            //while( !reader.atEnd() ) {
            //reader.readNext();
            //if( reader.isStartElement() ) {
            //auto name = reader.name();
            //if( name == "band" ) {
            //m_data += reader.readElementText();
            //return true;
            //}
            //}
            //reader.readNext();
            //}
            //reader.readNext();
            //text += reader.text().toString();
            //reader.text().toString();

            return true;
        }

        void	Parser::createWidget() {
            m_widget = QWidgetPtr( new QWidget() );
            m_widget->resize( 600, 400 );

            QTextBrowser * browser = new QTextBrowser();
            browser->setText( m_report->asHTML() );

            QVBoxLayout * layout = new QVBoxLayout( m_widget.data() );
            layout->setMargin( 0 );
            layout->addWidget( browser );
        }


        const ReportPtr			Parser::getReport() const {
            return m_report;
        }

        const QString			Parser::getLastError() const {
            return m_lastError;
        }

        const QWidgetPtr		Parser::getWidget() const {
            return m_widget;
        }

        const QVector< Style >	Parser::getStyles() const {
            return m_styles;
        }

    }
}
