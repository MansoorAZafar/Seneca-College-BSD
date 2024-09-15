import Button from 'react-bootstrap/Button';
import Container from 'react-bootstrap/Container';
import Form from 'react-bootstrap/Form';
import Nav from 'react-bootstrap/Nav';
import Navbar from 'react-bootstrap/Navbar';
import NavDropdown from 'react-bootstrap/NavDropdown';
import { useRouter } from "next/router";
import { useEffect, useState } from "react";

export default function Top() {
  const router = useRouter();
  const [recentlyViewed, setRecentlyViewed] = useState([]);
  const [names, setNames] = useState([]);

  useEffect(() => {
    if (recentlyViewed.length >= 5) {
      recentlyViewed.shift();
      names.shift();
    }
    if (router.query.display) {
      setRecentlyViewed([...recentlyViewed, JSON.parse(router.query.display).id]);
      setNames([...names, JSON.parse(router.query.display).name])
    }
  }, [router.query.display]);

  return (
    <Navbar expand="lg" className="bg-body-tertiary">
      <Container fluid>
        <Navbar.Brand onClick={() => router.push("/")}>Weather Application</Navbar.Brand>
        <Navbar.Toggle aria-controls="navbarScroll" />
        <Navbar.Collapse id="navbarScroll">
          <Nav
            className="me-auto my-2 my-lg-0"
            style={{ maxHeight: '100px' }}
            navbarScroll>
            <Nav.Link onClick={() => router.push("/")}>Home</Nav.Link>
            <NavDropdown title="Recently Visited" id="navbarScrollingDropdown" className="me-2">
              {recentlyViewed && recentlyViewed.length > 0 &&
               recentlyViewed.map((val, key) => {
                  return( 
                  <div key={key}>
                    <NavDropdown.Item key={key} onClick={() => router.push(`/searchCityID/${val}`)}>{names[key]}</NavDropdown.Item>
                    <NavDropdown.Divider key={val}/>
                  </div>
            )})}
            </NavDropdown>
          </Nav>
        </Navbar.Collapse>
      </Container>
    </Navbar>
  );
}
