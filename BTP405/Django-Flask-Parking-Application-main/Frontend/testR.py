import unittest
from unittest.mock import patch, MagicMock
from flask import session,url_for
from app import app

class TestFlaskApp(unittest.TestCase):

    def setUp(self):
        self.app = app.test_client()
        self.app.testing = True
    

    def test_home(self):
        response = self.app.get('/')
        self.assertEqual(response.status_code, 200)
        self.assertIn(b'Home Page', response.data)

    def test_register_page(self):
        response = self.app.get('/register')
        self.assertEqual(response.status_code, 200)
        self.assertIn(b'Register Page', response.data)

    def test_login_page(self):
        response = self.app.get('/login')
        self.assertEqual(response.status_code, 200)
        self.assertIn(b'Login Page', response.data)
        
            
    @patch('app.requests.get')
    def test_to_reserve_route(self, mock_get):
        # Set up a fake session with 'username' key
        with self.app as client:
            with client.session_transaction() as sess:
                sess['username'] = 'testuser'

            # Mock the requests.get method
            mock_get.return_value.json.return_value = {'reservations': []}

            # Simulate a GET request to the to_reserve route
            response = client.get('/reserve')

            # Assert that the response status code is 200
            self.assertEqual(response.status_code, 200)

            # Assert that requests.get was called with the correct URL
            mock_get.assert_called_once_with('https://database-api-latest.onrender.com/myapp/get_your_reservations/?username=testuser')

            # Assert that 'username' is set in the session
            self.assertIn('username', session)
            
                    
    @patch('app.requests.get')
    def test_do_admin_login_correct_credentials(self, mock_get):
        # Mock the response from the API
        mock_response = MagicMock()
        mock_response.status_code = 200
        mock_get.return_value = mock_response

        # Make a POST request to the login route
        response = self.app.post('/login', data={'username': 'test_user', 'password': 'test_password'})
        
        # Check if session variables are set and user is redirected
        with self.app as c:
            with c.session_transaction() as sess:
                self.assertEqual(sess['username'], 'test_user')
                self.assertTrue(sess['logged_in'])
        
        # Check if the response is a redirect to main
        self.assertEqual(response.status_code, 200)  # Status code should be 200
        
    @patch('app.requests.get')
    def test_do_admin_login_incorrect_credentials(self, mock_get):
        # Mock the response from the API
        mock_response = MagicMock()
        mock_response.status_code = 401  # Unauthorized
        mock_get.return_value = mock_response

        # Make a POST request to the login route with incorrect credentials
        response = self.app.post('/login', data={'username': 'test_user', 'password': 'wrong_password'})
        
        # Check if session variables are not set and user is redirected
        with self.app as c:
            with c.session_transaction() as sess:
                self.assertNotIn('username', sess)
                self.assertNotIn('logged_in', sess)
        
        # Check if the flash message "Wrong password!" is present
        with self.app.session_transaction() as sess:
            flashed_messages = sess.get('_flashes', [])
            self.assertTrue(any('Wrong password!' in message for message in flashed_messages))
    
        self.assertEqual(response.status_code, 200)  # Check if the status code is correct
        
        
    @patch('app.render_template')
    def test_logout(self, mock_render_template):
        with self.app as c:
            with c.session_transaction() as sess:
                sess['logged_in'] = True
                sess['username'] = 'test_user'

            # Make a GET request to the logout route
            response = c.get('/logout')

            # Check if session variables are set correctly
            self.assertFalse(session['logged_in'])  # Check if 'logged_in' is set to False
            self.assertEqual(session['username'], '')  # Check if 'username' is set to an empty string

            # Check if the logout route returns the 'home.html' template
            mock_render_template.assert_called_once_with('home.html')

            # Check if the response status code is 200
            self.assertEqual(response.status_code, 200)   
            
            
    @patch('app.render_template')
    def test_main_route_user_logged_in(self, mock_render_template):
        # Set 'logged_in' session variable to True
        with self.app as c:
            with c.session_transaction() as sess:
                sess['logged_in'] = True

            # Simulate a GET request to the main route
            response = c.get('/main')

            # Assert that render_template is called with 'main.html'
            mock_render_template.assert_called_once_with('main.html')

            # Assert that the response status code is 200
            self.assertEqual(response.status_code, 200)

    @patch('app.render_template')
    def test_main_route_user_not_logged_in(self, mock_render_template):
        # Set 'logged_in' session variable to False
        with self.app as c:
            with c.session_transaction() as sess:
                sess['logged_in'] = False

            # Simulate a GET request to the main route
            response = c.get('/main')

            # Assert that render_template is called with 'login.html'
            mock_render_template.assert_called_once_with('login.html')

            # Assert that the response status code is 200
            self.assertEqual(response.status_code, 200)
            
            
    @patch('app.render_template')
    def test_post_feedback(self, mock_render_template):
        # Simulate a POST request to the feedback route
        with self.app as c:
            response = c.post('/feedback')

            # Assert that the response status code is 200
            self.assertEqual(response.status_code, 200)        
            
    
    @patch('app.render_template')
    def test_to_feedback(self, mock_render_template):
        # Simulate a GET request to the feedback route
        with self.app as c:
            response = c.get('/feedback')

            # Assert that render_template is called once with the correct template name
            mock_render_template.assert_called_once_with('feedback.html')

            # Assert that the response status code is 200
            self.assertEqual(response.status_code, 200)
            
    @patch('app.requests.delete')
    @patch('app.render_template')
    def test_remove_reserve_success(self, mock_render_template, mock_delete):
        # Simulate a session with a reservation
        with self.app as c:
            with c.session_transaction() as sess:
                sess['reservations'] = [{'Slot_ID_id': '123'}]

            # Mock the response from the API
            mock_response = MagicMock()
            mock_response.json.return_value = {'message': 'Reservation removed successfully'}
            mock_delete.return_value = mock_response

            # Simulate a POST request to the reserve route
            response = c.post('/reserve')

            # Assert that requests.delete was called with the correct URL and data
            mock_delete.assert_called_once_with('https://database-api-latest.onrender.com/myapp/remove_reservation/', json={"slot_id": '123'})

            # Assert that render_template is called once with the correct template name and message
            mock_render_template.assert_called_once_with('success.html', message='Reservation removed successfully')

            # Assert that the response status code is 200
            self.assertEqual(response.status_code, 200)   
            
    @patch('app.requests.get')
    @patch('app.render_template')
    def test_to_reserve_with_reservation(self, mock_render_template, mock_get):
        # Simulate a session with a username
        with self.app as c:
            with c.session_transaction() as sess:
                sess['username'] = 'test_user'

            # Mock the response from the API
            mock_response = MagicMock()
            mock_response.json.return_value = {'reservations': [{'slot_id': '123', 'time': '10:00 AM'}, {'slot_id': '456', 'time': '12:00 PM'}]}
            mock_get.return_value = mock_response

            # Simulate a GET request to the reserve route
            response = c.get('/reserve')

            # Assert that requests.get was called with the correct URL
            mock_get.assert_called_once_with('https://database-api-latest.onrender.com/myapp/get_your_reservations/?username=test_user')

            # Assert that session['reservations'] is set correctly
            self.assertEqual(session['reservations'], [{'slot_id': '123', 'time': '10:00 AM'}, {'slot_id': '456', 'time': '12:00 PM'}])

            # Assert that render_template is called once with the correct template name and reservation
            mock_render_template.assert_called_once_with('reserve.html', reservation=[{'slot_id': '123', 'time': '10:00 AM'}, {'slot_id': '456', 'time': '12:00 PM'}])

            # Assert that the response status code is 200
            self.assertEqual(response.status_code, 200)

    @patch('app.requests.get')
    @patch('app.render_template')
    def test_to_reserve_without_reservation(self, mock_render_template, mock_get):
        # Simulate a session with a username
        with self.app as c:
            with c.session_transaction() as sess:
                sess['username'] = 'test_user'

            # Mock the response from the API
            mock_response = MagicMock()
            mock_response.json.return_value = {'reservations': []}
            mock_get.return_value = mock_response

            # Simulate a GET request to the reserve route
            response = c.get('/reserve')

            # Assert that requests.get was called with the correct URL
            mock_get.assert_called_once_with('https://database-api-latest.onrender.com/myapp/get_your_reservations/?username=test_user')

            # Assert that session['reservations'] is set correctly
            self.assertEqual(session['reservations'], "No Reservation")

            # Assert that render_template is called once with the correct template name and reservation
            mock_render_template.assert_called_once_with('reserve.html', reservation="No Reservation")

            # Assert that the response status code is 200
            self.assertEqual(response.status_code, 200)  
            
    @patch('app.render_template')
    def test_success(self, mock_render_template):
        # Simulate a GET request to the success route
        with self.app as c:
            response = c.get('/success')

            # Assert that render_template is called once with the correct template name
            mock_render_template.assert_called_once_with('success.html')

            # Assert that the response status code is 200
            self.assertEqual(response.status_code, 200) 
            
    @patch('app.render_template')
    def test_reserve(self, mock_render_template):
        # Set up a mock session with slot and type
        with self.app as c:
            with c.session_transaction() as sess:
                sess['slot'] = 'some_slot_value'
                sess['type'] = 'some_type_value'

            # Simulate a GET request to the reserve route
            response = c.get('/makeReserve')

            # Assert that render_template is called once with the correct arguments
            mock_render_template.assert_called_once_with('makeReserve.html', slot='some_slot_value', type='some_type_value')

            # Assert that the response status code is 200
            self.assertEqual(response.status_code, 200)   
            
    
    @patch('app.requests.post')
    def test_register_user_success(self, mock_post):
        # Mock the response from the API
        mock_response = MagicMock()
        mock_response.json.return_value = {'message': 'User added successfully'}
        mock_post.return_value = mock_response

        # Simulate a POST request to the register route with matching passwords
        with self.app as c:
            response = c.post('/register', data={'username': 'test_user', 'password': 'password', 'password2': 'password'})

            # Assert that requests.post was called with the correct URL and data
            mock_post.assert_called_once_with('https://database-api-latest.onrender.com/myapp/add_user/', json={'username': 'test_user', 'password': 'password'})

            # Assert that the response status code is 200
            self.assertEqual(response.status_code, 200)

            # Assert that the response contains the home template
            self.assertIn(b'Home Page', response.data)

    @patch('app.requests.post')
    def test_register_user_password_mismatch(self, mock_post):
        # Simulate a POST request to the register route with mismatching passwords
        with self.app as c:
            response = c.post('/register', data={'username': 'test_user', 'password': 'password1', 'password2': 'password2'})

            # Assert that requests.post is not called
            mock_post.assert_not_called()

            # Assert that the response status code is 200
            self.assertEqual(response.status_code, 200)

            # Assert that the response contains the error message
            self.assertIn(b'<p>Password missmatch</p>', response.data)  
            
    @patch('app.requests.get')
    def test_to_parking(self, mock_get):
        # Mock the response from the API
        mock_response = MagicMock()
        mock_response.json.return_value = {'available_locations': [{'id': 1, 'type': 'inner'}, {'id': 2, 'type': 'outter'}]}
        mock_get.return_value = mock_response

        # Simulate a GET request to the parking route
        with self.app as c:
            response = c.get('/parking')

            # Assert that requests.get was called with the correct URL
            mock_get.assert_called_once_with('https://database-api-latest.onrender.com/myapp/get_available_locations/')

            # Assert that the response status code is 200
            self.assertEqual(response.status_code, 200)

            # Assert that the response contains the parking template
            self.assertIn(b'inner', response.data)  # Assuming 'Standard' appears in the template
            self.assertIn(b'outter', response.data)   # Assuming 'Premium' appears in the template
            
            
   
    @patch('app.requests.post')
    def test_reserve_slot_success(self, mock_post):
        # Mock the response from the API
        mock_response = MagicMock()
        mock_response.json.return_value = {'message': 'Reservation successful'}
        mock_post.return_value = mock_response

        # Simulate a POST request to the reserveSlot route with form data
        with self.app as c:
            with c.session_transaction() as sess:
                sess['username'] = 'test_user'
                sess['slot'] = '12345'  # Assuming this is the slot ID
            response = c.post('/makeReserve', data={'hours': '2'})

            # Assert that requests.post was called with the correct URL and data
            mock_post.assert_called_once_with(
                'https://database-api-latest.onrender.com/myapp/add_reservation/',
                json={'username': 'test_user', 'slot_id': 12345, 'expiry_hours': 2}
            )

            # Assert that the response status code is 200 (success)
            self.assertEqual(response.status_code, 200)         

            # Assert that the message is passed to the template correctly
            self.assertIn(b'Reservation successful', response.data)   
            
if __name__ == '__main__':
    unittest.main()
