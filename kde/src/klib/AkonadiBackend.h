/************************************************************************************
 *   Copyright (C) 2009 by Savoir-Faire Linux                                       *
 *   Author : Jérémy Quentin <jeremy.quentin@savoirfairelinux.com>                  *
 *            Emmanuel Lepage Vallee <emmanuel.lepage@savoirfairelinux.com>         *
 *                                                                                  *
 *   This library is free software; you can redistribute it and/or                  *
 *   modify it under the terms of the GNU Lesser General Public                     *
 *   License as published by the Free Software Foundation; either                   *
 *   version 2.1 of the License, or (at your option) any later version.             *
 *                                                                                  *
 *   This library is distributed in the hope that it will be useful,                *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of                 *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU              *
 *   Lesser General Public License for more details.                                *
 *                                                                                  *
 *   You should have received a copy of the GNU Lesser General Public               *
 *   License along with this library; if not, write to the Free Software            *
 *   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA *
 ***********************************************************************************/

#ifndef AKONADI_BACKEND_H
#define AKONADI_BACKEND_H

#include "../lib/ContactBackend.h"
#include "../lib/CallModel.h"
#include "../lib/typedefs.h"
#include <akonadi/collectionmodel.h>

//Qt
class QObject;

//KDE
namespace KABC {
   class Addressee;
   class AddresseeList;
}

namespace Akonadi {
   class Session;
   class CollectionModel;
   class Collection;
}

//SFLPhone
class Contact;

///@class AkonadiBackend Implement a backend for Akonadi
class LIB_EXPORT AkonadiBackend : public ContactBackend {
   Q_OBJECT
public:
   static   ContactBackend* getInstance();
   Contact* getContactByPhone ( const QString& phoneNumber ,bool resolveDNS = false );
   Contact* getContactByUid   ( const QString& uid                                  );
   void     editContact       ( Contact*       contact , QWidget* parent = 0        );
   void     addNewContact     ( Contact*       contact , QWidget* parent = 0        );
   
   virtual void     editContact   ( Contact*   contact                              );
   virtual void     addNewContact ( Contact*   contact                              );

private:
   AkonadiBackend(QObject* parent);
   virtual ~AkonadiBackend();

   //Helper
   QString getUserFromPhone(QString phoneNumber);
   QString getHostNameFromPhone(QString phoneNumber);

   //Attributes
   static AkonadiBackend*         m_pInstance  ;
   static CallModel<>*            m_pModel     ;
   Akonadi::Session*              m_pSession   ;
   Akonadi::Collection            m_Collection ;
   QHash<QString,KABC::Addressee> m_AddrHash   ;
   ContactList                    m_pContacts  ;

protected:
   ContactList update_slot();

public slots:
   ContactList update(Akonadi::Collection collection);
   void collectionsReceived( const Akonadi::Collection::List& );

signals:
   void collectionChanged();
};

#endif